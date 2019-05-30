//
//  MeshService.h
//  office
//
//  Created by yqf on 16/11/17.
//  Copyright © 2016年 Jonathan. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import <UIKit/UIKit.h>

#import "BleUtil.h"
#import "TPMesh.h"
#import "TPDevice.h"
#import "TPGroup.h"
#import "TPScene.h"
#import "TPScan.h"
#import "TPFileManager.h"
#import "MeshDev.h"
#import "MeshFunc.h"
#import "UnitInfo.h"
#import "DeviceBean.h"
#import <pl_encry_mesh/encry_mesh.h>

#define NSLog(format, ...) do { \
fprintf(stderr, "<%s : %d> %s\n", \
[[[NSString stringWithUTF8String:__FILE__] lastPathComponent] UTF8String], \
__LINE__, __func__); \
(NSLog)((format), ##__VA_ARGS__); \
} while (0)

#define     CHANNEL_0   (Byte) 0x20
#define     CHANNEL_1   (Byte) 0x21
#define     CHANNEL_2   (Byte) 0x22
#define     CHANNEL_3   (Byte) 0x23
#define     CHANNEL_4   (Byte) 0x24
#define     CHANNEL_5   (Byte) 0x25
#define     CHANNEL_6   (Byte) 0x26
#define     CHANNEL_7   (Byte) 0x27
#define     CHANNEL_8   (Byte) 0x28
#define     CHANNEL_9   (Byte) 0x29
#define     CHANNEL_10  (Byte) 0x2a
#define     CHANNEL_11  (Byte) 0x2b
#define     CHANNEL_12  (Byte) 0x2c
#define     CHANNEL_13  (Byte) 0x2d
#define     CHANNEL_14  (Byte) 0x2e
#define     CHANNEL_15  (Byte) 0x2f
#define     CHANNEL_16  (Byte) 0x30
#define     CHANNEL_17  (Byte) 0x31
#define     CHANNEL_18  (Byte) 0x32
#define     CHANNEL_19  (Byte) 0x33
#define     CHANNEL_20  (Byte) 0x34
#define     CHANNEL_21  (Byte) 0x35
#define     CHANNEL_22  (Byte) 0x36
#define     CHANNEL_23  (Byte) 0x37
#define     CHANNEL_24  (Byte) 0x38
#define     CHANNEL_25  (Byte) 0x39
#define     CHANNEL_26  (Byte) 0x3a
#define     CHANNEL_27  (Byte) 0x3b
#define     CHANNEL_28  (Byte) 0x3c
#define     CHANNEL_29  (Byte) 0x3d
#define     CHANNEL_30  (Byte) 0x3e
#define     CHANNEL_31  (Byte) 0x3f

#pragma mark - **************** app状态
#define APP_EXIT_MESH       1
#define APP_JOINNING_MESH   2
#define APP_JOINED_MESH     3

#pragma mark - **************** 返回值定义
#define RET_RESULT_FALSE            0
#define RET_RESULT_TRUE             1
#define RET_ERROR_INVALID_HOMEID    2
#define RET_ERROR_DUP_MESH          3
#define RET_ERROR_DUP_HOMEID        4

#pragma mark - **************** Mesh UI TAG
#define UI_GROUP_ID_NONE    -1      // "未分组"的groupId为-1
#define UI_MESH_EXIST_TAG   100     // 周围存在mesh网络
#define UI_MESH_NONE_TAG    200     // 周围不存在的mesh网络，之前扫描到 或 创建的mesh网络
#define UI_MESH_ADD         50000   // "添加网络"的tag为50000开始
#define UI_GROUP_ADD 99 //"添加group"的tag为99
#define UI_GROUP_TAG 100 // group的tag从100开始

#define MESH_RSSI 	@"_mesh_rssi"

#define NOTIFY_REFRESH_UI           @"notifyRefreshUI"
#define PL_ADDR_ALL 				(short) 0xffff

#define ADD_DEVICE_NONE		0
#define ADD_DEVICE_START	1
#define ADD_DEVICE_PROCESS	2
#define ADD_DEVICE_OK		3
#define ADD_DEVICE_FAILED	4

#define MeshStatusScaning			0x0000
#define MeshStatusConnecting		0x0001
#define MeshStatusReconnecting		0x0002
#define MeshStatusConnected			0x0003
#define MeshStatusConnectionReady	0x0004
#define MeshStatusDisconnected		0x0005
#define MeshStatusWelcome			0x0006
#define MeshStatusMeshChanged		0x0007
#define MeshStatusMeshListChanged	0x0008
#define MeshStatusWrongPwd			0x0009
#define MeshStatusAlreadyConnected  0x000a
#define MeshStatusPeripheral 		0x000b
	
typedef NS_ENUM(NSInteger, LIB_TYPE){
    LIB_DIRECT_TRANSMIT = 0,
    LIB_ODELIC,//节点变化时,主动发送ping all命令
    LIB_DING,//节点变化时,主动发送ping all命令
    LIB_NPING,//节点变化时,不主动发送ping all命令
    LIB_END
};

typedef NS_ENUM(NSInteger, LIGHT_CMD_TYPE){
    LIGHT_CMD_NONE = 0,
    LIGHT_CMD_SINGLE,//单灯控制
    LIGHT_CMD_GROUP,//组控制
    LIGHT_CMD_ALL,//所有节点控制
    LIGHT_CMD_END
};

//mesh表格item类型
typedef NS_ENUM(NSInteger, MESH_ITEM_TYPE){
    MESH_ITEM_NONE = 0,
    MESH_ITEM_GET_MAX_GROUP_ID,//最大组号
    MESH_ITEM_GET_CTL_GROUP_ID,//当前控制的组
    MESH_ITEM_GET_CONFIG_GROUP_ID,//当前配置的组
    MESH_ITEM_GET_SCENE_ID,//当前选择的场景
    MESH_ITEM_GET_PRODUCT_ID,//当前选择的产品
    MESH_ITEM_GET_CTL_GROUP_UPDATE,//当前控制组是否更新
    MESH_ITEM_GET_SCENE_UPDATE,//当前场景是否更新
    MESH_ITEM_GET_PRODUCT_UPDATE,//当前选择的产品是否更新
    
    MESH_ITEM_SET_MAX_GROUP_ID,
    MESH_ITEM_SET_CTL_GROUP_ID,
    MESH_ITEM_SET_CONFIG_GROUP_ID,
    MESH_ITEM_SET_SCENE_ID,
    MESH_ITEM_SET_PRODUCT_ID,
    MESH_ITEM_SET_CTL_GROUP_UPDATE,
    MESH_ITEM_SET_SCENE_UPDATE,
    MESH_ITEM_SET_PRODUCT_UPDATE,
    MESH_ITEM_SET_TAG,
	MESH_ITEM_SET_NAME,
	MESH_ITEM_SET_RSSI,
	MESH_ITEMS_RESET_NAME,
    MESH_ITEMS_RESET_TAG,
    
    MESH_ITEM_DEL_PWD, //删除pwd为-1的临时网络
    MESH_ITEM_DEL_HOMEID,//删除指定homeID的网络
    MESH_ITEM_DEL_NAME,//删除指定name的网络
};

typedef NS_ENUM(NSInteger, MESH_SHOW_TYPE){
    MESH_SHOW_NONE = 0,//
    MESH_SHOW_NAME,//显示mesh网络的名称
    MESH_SHOW_HOMEID,//显示homeId
    MESH_SHOW_PWD,//显示mesh网络的密码
    MESH_SHOW_END
};

typedef NS_ENUM(NSInteger, GROUP_LIST_TYPE){
    GROUP_LIST_NORMAL = 0,//所有group item, 不包含未分组
    GROUP_LIST_ALL,//所有group item，包含未分组
    GROUP_LIST_NODES_ALL,//有节点的group item，包含未分组
    GROUP_LIST_NODES,//有节点的group item，不包含未分组
    GROUP_LIST_END
};

typedef NS_ENUM(NSInteger, NPING_PRODUCT_TYPE){
    NPING_PRODUCT_NORMAL = 0,
    NPING_PRODUCT_TWO_BUTTON = 0x4001,
    NPING_PRODUCT_SCENE_BUTTON = 0X4002,
    NPING_PRODUCT_LIGHT = 0X5001,
    NPING_PRODUCT_PERSON = 0X5002,
    NPING_PRODUCT_END
};

typedef NS_ENUM(NSInteger, TABLE_TYPE){
    TABLE_NONE = 0,
    TABLE_MESH,   	//mesh表格
    TABLE_DEVICE, 	//device表格
    TABLE_GROUP_TARGET,  //指定mesh的group name
    TABLE_GROUP_ALL,     //所有mesh的group name
    TABLE_SCENE_TARGET,  //指定mesh的scene name
    TABLE_SCENE_ALL, 	 //所有mesh的scene name
    TABLE_SCAN, //所有扫描到的沙发设备

    BLET_END
};



@protocol MeshCallback <NSObject>

@optional

-(void)on_recv_mesh_data:(Byte)channel data:(NSData *)data broadcast_flag:(BOOL)broadcast_flag;
-(void)on_connection_state_changed:(BOOL)state;
-(void)on_device_num_changed:(int)current all:(int)all;
-(void)on_homeId_found:(NSString *)homeId;

-(void)on_update_device_list;
-(void)on_discoverable_device_found:(TPScan *)scanDevice;
-(void)get_homeid_pwd:(NSString *)homeId pwd:(NSString *)pwd;
-(void)on_device_add_status:(NSString *)uuid status:(int)status;
-(void)on_mesh_status_changed:(NSString *)uuid status:(int)status;

// model callbak
-(void)onOnoffStatus:(Byte) srcType addr:(Byte *) addr unitIndex:(Byte) unitIndex onoff:(Byte) onoff;
-(void)onLevelStatus:(Byte) srcType addr:(Byte *) addr unitIndex:(Byte) unitIndex level:(short) level;
-(void)onGroupStatus:(Byte) srcType addr:(Byte *) addr status:(Byte) status groupId:(Byte)groupId deviceBean:(DeviceBean *)deviceBean;
-(void)onSceneRegStoreStatus:(Byte) srcType addr:(Byte *) addr unitIndex:(Byte) unitIndex status:(Byte) status sceneId:(Byte) sceneId;
-(void)onSceneRegDeleteStatus:(Byte) srcType addr:(Byte *) addr unitIndex:(Byte) unitIndex status:(Byte) status sceneId:(Byte) sceneId;
-(void)onSceneRegStatus:(Byte) srcType addr:(Byte *) addr unitIndex:(Byte) unitIndex status:(Byte) status sceneList:(NSArray *) sceneList;
-(void)onSceneRecallStatus:(Byte) srcType addr:(Byte *) addr unitIndex:(Byte) unitIndex status:(Byte) status sceneId:(Byte) sceneId;
-(void)onDeviceExited:(Byte) srcType addr:(Byte *) addr status:(Byte) status;
-(void)onDeviceDeleted:(Byte) srcType addr:(Byte *) addr status:(Byte) status;
-(void)onDeviceRebooted:(Byte) srcType addr:(Byte *) addr;
-(void)onMeshNameChanged:(Byte) srcType addr:(Byte *) addr status:(Byte) status name:(NSString *)name;
-(void)onDeviceNameChanged:(Byte) srcType addr:(Byte *) addr status:(Byte) status name:(NSString *)name;

@end

@interface MeshService : NSObject

#pragma mark - **************** common API
+(MeshService *)getInstance;
-(void)API_start_scan;
-(void)API_register_mesh_data_callback:(id<MeshCallback>)callback;
-(void)API_unregister_mesh_data_callback:(id<MeshCallback>)callback;
-(int)API_set_mesh_info:(NSString *)name homeId:(NSString*)homeId pwd:(NSString*)pwd rssi:(int)rssi;
-(void)API_create_mesh_encry;
-(void)API_add_device:(NSString *)uuid;
-(void)API_exit_create_mesh;
-(void)API_join_mesh;
-(void)API_exit_mesh;
-(BOOL)API_get_connection_status;
-(int)API_get_all_devices_num;
-(int)API_get_current_devices_num;
-(NSArray *)API_get_device_list;
-(void)pingAll;

-(void)API_register_mesh_data_channel:(Byte)channel;
-(void)API_unregister_mesh_data_channel:(Byte)channel;

-(int)API_get_rssi:(NSString *)homeId;
-(void)API_rescan;
-(void)API_stop_scan;

-(NSArray *)API_DB_mesh_get_list:(BOOL)isAll;
-(void)ping:(Byte *)targetVaddr;


-(NSMutableArray *)API_get_unitInfoList:(NSString *)btAddr;
//--------- model
-(int) exitDevice:(Byte *)vAddr;
-(int) deleteDevice:(Byte *)vAddr;
-(int) rebootDevice:(Byte *)vAddr;
-(int) onoffSet:(Byte *) targetVaddr unitIndex:(int) unitIndex onoff:(BOOL) onoff ackType:(Byte) ackType;
-(int) onoffSetGroup:(Byte) groupId onoff:(BOOL) onoff ackType:(Byte) ackType;
-(int) onoffSetAll:(BOOL) onoff ackType:(Byte) ackType;
-(int) onoffBtAddrSet:(Byte *) btAddr unitIndex:(int) unitIndex onoff:(BOOL) onoff ackType:(Byte) ackType;
-(int) onoffToggle:(Byte *) targetVaddr unitIndex:(int) unitIndex ackType:(Byte) ackType;
-(int) onoffToggleGroup:(Byte) groupId ackType:(Byte) ackType;
-(int) onoffToggleAll:(Byte) ackType;
-(int) levelSet:(Byte *) targetVaddr unitIndex:(int) unitIndex level:(short) level ackType:(Byte) ackType;
-(int) levelSetGroup:(Byte) groupId level:(short) level ackType:(Byte) ackType;
-(int) levelSetAll:(short) level ackType:(Byte) ackType;
-(int) levelDeltaSet:(Byte *) targetVaddr unitIndex:(int) unitIndex level:(int) level ackType:(Byte) ackType;
-(int) ctlSet:(Byte *) targetVaddr unitIndex:(int) unitIndex lightness:(short) lightness temperature:(short) temperature deltaUv:(short) deltaUv ackType:(Byte) ackType;
-(int) ctlSetGroup:(Byte) groupId lightness:(short) lightness temperature:(short) temperature deltaUv:(short) deltaUv ackType:(Byte) ackType;
-(int) ctlSetAll:(short) lightness temperature:(short) temperature deltaUv:(short) deltaUv ackType:(Byte) ackType;
-(int) hslSet:(Byte *) targetVaddr unitIndex:(int) unitIndex lightness:(short) lightness hue:(short) hue saturation:(short) saturation ackType:(Byte) ackType;
-(int) hslSetGroup:(Byte) groupId lightness:(short) lightness hue:(short) hue saturation:(short) saturation  ackType:(Byte) ackType;
-(int) hslSetAll:(short) lightness hue:(short) hue saturation:(short) saturation ackType:(Byte) ackType;
-(int) vendorSend:(Byte*) targetVaddr unitIndex:(int) unitIndex vendorOp:(short) vendorOp data:(Byte *) data len:(int)len;
-(int) vendorSendGroup:(Byte) groupId vendorOp:(short) vendorOp data:(Byte *) data len:(int)len;
-(int) vendorSendAll:(short) vendorOp data:(Byte *) data len:(int)len;
-(int) sceneAdd:(Byte *) targetVaddr unitIndex:(int) unitIndex sceneId:(Byte) sceneId ackType:(Byte) ackType;
-(int) sceneAddGroup:(Byte) groupId sceneId:(Byte) sceneId ackType:(Byte) ackType;
-(int) sceneAddAll:(Byte) sceneId ackType:(Byte) ackType;
-(int) sceneDel:(Byte *) targetVaddr unitIndex:(int) unitIndex sceneId:(Byte) sceneId ackType:(Byte) ackType;
-(int) sceneDelGroup:(Byte) groupId sceneId:(Byte) sceneId ackType:(Byte) ackType;
-(int) sceneDelAll:(Byte) sceneId ackType:(Byte) ackType;
-(int) sceneGet:(Byte *) targetVaddr unitIndex:(int) unitIndex;
-(int) sceneGetGroup:(Byte) groupId;
-(int) sceneGetAll;
-(int) sceneRecall:(Byte *) targetVaddr unitIndex:(int) unitIndex sceneId:(Byte) sceneId ackType:(Byte) ackType;
-(int) sceneRecallGroup:(Byte) groupId sceneId:(Byte) sceneId ackType:(Byte) ackType;
-(int) sceneRecallAll:(Byte) sceneId ackType:(Byte) ackType;

-(BOOL)API_send_profile_data:(Byte *)vAddr data:(Byte *)data len:(short) len;
-(BOOL)API_send_btmac_profile_data:(Byte *)btAddr data:(Byte *)data len:(short) len;
-(int) addGroups:(Byte*) targetVaddr unitIndex:(int) unitIndex groupId:(int) groupId ackType:(Byte) ackType;
-(int) delGroups:(Byte*) targetVaddr unitIndex:(int) unitIndex groupId:(int) groupId ackType:(Byte) ackType;
-(int) meshNameSet:(Byte *) targetVaddr data:(Byte *) data len:(int)len ackType:(Byte) ackType;
-(int) meshNameSetAll:(Byte *) data len:(int)len ackType:(Byte) ackType;
-(int) meshNameSetGroup:(Byte) groupId data:(Byte *) data len:(int)len ackType:(Byte) ackType;
-(int) meshNameGet:(Byte *) targetVaddr;
-(int) deviceNameSet:(Byte *) targetVaddr data:(Byte *) data len:(int)len ackType:(Byte) ackType;
-(int) deviceNameSetAll:(Byte *) data len:(int)len ackType:(Byte) ackType;
-(int) deviceNameSetGroup:(Byte) groupId data:(Byte *) data len:(int)len ackType:(Byte) ackType;
-(int) deviceNameGet:(Byte *) targetVaddr;

#pragma mark - **************** other API

-(NSString*)API_get_mesh_name;
-(NSString*)API_get_homeid;
-(NSString*)API_get_mesh_name:(NSString *)homeId;
-(void)API_set_mesh_name:(NSString*)name;
-(NSString*)API_get_pwd:(NSString *)name;
-(BOOL)API_DB_update_mesh_name:(NSString *)newName oldName:(NSString *)oldName;

-(void)API_remove_local_mesh:(NSString *)title;
-(void)API_set_all_on_off:(int)state;
-(BOOL)API_get_all_on_off;

-(BOOL)API_CMD_remove_device:(int)vAddr;
-(BOOL)API_CMD_send_pwm:(int)vAddr data:(NSData*)data;
-(BOOL)API_send_user_defined_data:(int)vAddr channel:(Byte)channel data:(NSData*)data;
-(BOOL)API_CMD_ping_all;

-(BOOL)API_CMD_set_light_xy:(int)type vAddr:(int)vAddr groupId:(int)group_id posX:(int)posX posY:(int)posY;
-(BOOL)API_CMD_set_group_onoff:(int)group_id all:(BOOL)isAll state:(BOOL)onOff;
-(BOOL)API_CMD_scene_play:(int)group_id scene:(int)scene_id all:(BOOL)isAll;
-(BOOL)API_CMD_set_single_onoff:(int)vAddr state:(BOOL)onOff;

-(BOOL)API_ping_all;

-(BOOL)API_CMD_set_group:(int)vAddr oldGroupId:(int)oldGroupId newGroupId:(int)newGroupId;
-(BOOL)API_CMD_unset_group:(int)vAddr groupId:(int)groupId;
-(BOOL)API_CMD_set_scene:(int)vAddr sceneId:(int)sceneId;
-(BOOL)API_CMD_unset_scene:(int)vAddr sceneId:(int)sceneId;
-(BOOL)API_CMD_scene_play:(int)vAddr sceneId:(int)sceneId;
-(int)API_get_app_state;
-(void)API_start_log_save;
-(void)API_list_log_files;
-(void)API_delete_log_files;

-(BOOL)API_DB_table_show:(TABLE_TYPE)tableType;

-(NSArray *)API_DB_device_get_group_list:(GROUP_LIST_TYPE)groupListType;
-(NSArray*)API_DB_device_get_group_name_list;
-(int)API_DB_device_get_num_in_group:(int)groupId;
-(BOOL)API_DB_device_insert_group_name:(int)groupId groupName:(NSString*)groupName;
-(void)API_DB_device_delete_group_name:(TPGroup *)groupName;
-(void)API_DB_device_insert:(TPDevice*)scene;
-(void)API_DB_device_update_groupId:(int)vAddr groupId:(int)groupId;
-(NSArray *)API_DB_device_get_product_list;
-(NSArray *)API_DB_device_get_group_device:(int)groupId;
-(int)API_DB_device_get_num_in_product:(int)companyId productId:(int)productId;
-(NSArray *)API_DB_device_get_list_in_product:(int)companyId productId:(int)productId;
-(NSArray *)API_DB_device_get_target:(NSString *)btAddr;
-(NSArray *)API_DB_device_get_list:(BOOL)singleCtl;
-(void)API_DB_device_update_name:(NSString*)btAddr name:(NSString*)name;

-(BOOL)API_set_lib_type:(LIB_TYPE)type;
-(LIB_TYPE)API_get_lib_type;

-(BOOL)API_DB_is_productIndex_unique:(int)groupId productIndex:(int)productIndex;

-(void)API_set_bright_delay:(float)delay;

-(int)API_DB_mesh_get_subItem:(MESH_ITEM_TYPE)itemType;
-(BOOL)API_DB_mesh_update_item:(MESH_ITEM_TYPE)itemType homeId:(NSString *)homeId itemValue:(int)itemValue;
-(BOOL)API_DB_mesh_delete_item:(MESH_ITEM_TYPE)itemType homeId:(NSString *)homeId name:(NSString *)name;

-(void)API_DB_delete_group_id:(int)groupId;
-(void)API_DB_update_group_name:(int)groupId groupName:(NSString *)groupName;

-(TPScene*)API_DB_scene_get_info:(int)sceneId;
-(BOOL)API_DB_scene_insert_info:(int)vAddr sceneId:(int)sceneId sceneName:(NSString*)sceneName;
-(void)API_DB_scene_delete_info:(int)sceneId;

-(void)API_set_mesh_show_type:(int)type;
-(int)API_get_mesh_show_type;
-(NSString *)API_get_meshLib_ver;
-(void)API_adv_homeid:(NSString *)homeId pwd:(NSString *)pwd;
-(void)API_stop_adv;
-(void)API_recv_homeId;
-(void)API_set_autoPing:(BOOL)autoPing;
-(void)API_DB_delete_scan;
-(NSArray *)API_DB_scan_list:(Boolean)isAll;
-(void)API_set_mesh_rssi:(int)rssi;
//-(BOOL)API_is_new_mesh:(NSString *)title;
-(void)send_notify_message:(NSString*)msg data:(NSDictionary *)sendData;
-(void)API_DB_show_mesh;
-(int)API_get_ping_state;
-(BOOL)API_CMD_send_uart:(int)vAddr channel:(int)channel data:(NSData*)data;
-(void)API_save_Func_device:(TPDevice *)device;
-(NSMutableArray *)API_get_callback;

@end


