//
//  BLEDeviceManager.h
//  Lamps
//
//  Created by yqf on 16/3/23.
//  Copyright © 2016年 jerryDing. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import "MouseletDevice.h"
#import "PLDevice.h"
#import "BleUtil.h"

//#define NSLog(format, ...) do { \
//fprintf(stderr, "<%s : %d> %s\n", \
//[[[NSString stringWithUTF8String:__FILE__] lastPathComponent] UTF8String], \
//__LINE__, __func__); \
//(NSLog)((format), ##__VA_ARGS__); \
//} while (0)

typedef NS_ENUM(NSInteger, BLE_STATE_TYPE){
    BLE_STATE_NONE = 0,
    BLE_STATE_CONNECTING,
    BLE_STATE_CONNECTED,
    BLE_STATE_SERVICE_DISCOVER,
    BLE_STATE_DISCONNECT,       //和一个设备断开连接
    BLE_STATE_DISCONNECT_ALL,   //和所有设备断开连接
    BLE_STATE_END
};

typedef NS_ENUM(NSInteger, BLE_UPDATE_LIST_TYPE){
    BLE_UPDATE_LIST_NONE = 0,
    BLE_UPDATE_LIST_SCAN,   //更新扫描的设备
    BLE_UPDATE_LIST_CONNECTED, //更新连接的设备
    BLE_UPDATE_LIST_END
};

typedef NS_ENUM(NSInteger, BLE_OPT_TYPE){
    BLE_OPT_NONE = 0,
    BLE_OPT_CONNECT_SINGLE,   //和单个设备建立连接
    BLE_OPT_CONNECT_CHOOSE,   //和选择的设备建立连接, 可以多个
    BLE_OPT_DISCONNECT_SINGLE,   //和单个设备断开连接
    BLE_OPT_DISCONNECT_CHOOSE,   //和选择的设备断开连接, 可以多个
    BLE_OPT_DISCONNECT_CHOOSE_R,   //和选择的设备断开连接, 可以多个, 程序进入后台断开所有连接，程序进入前台后需要重连
    BLE_OPT_END
};

typedef NS_ENUM(NSInteger, TABLE_DEVICE_TYPE){
    TABLE_DEVICE_NONE = 0,
    TABLE_DEVICE_SINGLE,   //指定uuid的设备
    TABLE_DEVICE_ALL,    //所有设备
    TABLE_DEVICE_BTADDR,   //指定btAddr的设备
    TABLE_DEVICE_SCAN,  //扫描到的设备
    TABLE_DEVICE_UNPROVISION,   //扫描到的unprovision设备
    TABLE_DEVICE_PROVISION,     //扫描到的provision设备
    TABLE_DEVICE_CHOOSE,//选择的设备
    TABLE_DEVICE_DISCONNECT,//断开连接的设备,即扫描到的设备，不包含已建立连接的设备
    TABLE_DEVICE_CONNECTED,//连接的设备

    TABLE_DEVICE_UPDATE_NAME,   //更新设备名称
    TABLE_DEVICE_UPDATE_BTADDR,  //更新btAddr
    TABLE_DEVICE_UPDATE_UUID,   //更新uuid
    TABLE_DEVICE_UPDATE_CHOOSE, //更新设备是否选择
    TABLE_DEVICE_UPDATE_FLAG, //更新设备是否为新设备
    TABLE_DEVICE_UPDATE_FLAG_ALL, //更新所有设备是否为新设备
    TABLE_DEVICE_UPDATE_CONNECT,  //更新设备连接状态,单个设备
    TABLE_DEVICE_UPDATE_CONNECT_ALL,//更新所有设备的连接状态
    TABLE_DEVICE_UPDATE_RSSI,   //更新设备RSSI
    TABLE_DEVICE_UPDATE_PROVISION, //更新设备Provision
    TABLE_DEVICE_UPDATE_ALL,   //更新所有字段
    TABLE_DEVICE_END
};

typedef NS_ENUM(NSInteger, SEND_DATA_TYPE){
    SEND_DATA_NONE = 0,
    SEND_DATA_SINGLE,  //发送数据给指定设备
    SEND_DATA_ALL,  //发送数据给所有已连接的设备
    SEND_DATA_END
};

//不同的类型，使用的特性不同
typedef NS_ENUM(NSInteger,LIB_TYPE){
    LIB_TYPE_NONE = 0,
    LIB_TYPE_SIG_MESH,  //sig mesh模式
    LIB_TYPE_END
};

@protocol BLECallback <NSObject>

@optional

-(void)on_connection_state_changed:(BLE_STATE_TYPE)stateType uuid:(NSString*)uuid;
-(void)on_update_device_list:(BLE_UPDATE_LIST_TYPE)updateType uuid:(NSString*)uuid advData:(NSData *)advData;
-(void)on_recv_data:(NSData *)data uuid:(NSString*)uuid;
-(void)on_send_timeout:(NSData *)data uuid:(NSString*)uuid;

@end


@interface BLEDeviceManager : NSObject

+(BLEDeviceManager *)getInstance;

-(void)API_start_scan;
-(void)API_stop_scan;
-(BOOL)API_get_connect_state;

-(BOOL)API_DB_device_insert_item:(MouseletDevice *)device;
-(BOOL)API_DB_device_insert_item:(NSString *)btAddr isChoose:(int)isChoose;
-(BOOL)API_DB_device_is_item_exist:(NSString *)gIdentify;
-(BOOL)API_DB_device_is_BTAddr_exist:(NSString *)btAddr;

-(NSArray*)API_DB_device_get_items:(TABLE_DEVICE_TYPE)itemType uuid:(NSString*)uuid;
-(void)API_DB_device_show:(TABLE_DEVICE_TYPE)itemType;
-(BOOL)API_DB_device_update:(TABLE_DEVICE_TYPE)itemType uuid:(NSString*)uuid name:(NSString*)name isChoose:(int)isChoose isConnected:(int)isConnected rssi:(int)rssi flag:(int)flag btAddr:(NSString *)btAddr provision:(int)provision;
-(int)API_DB_device_dump_choose;
-(BOOL)API_DB_device_isOpen_exist;
-(BOOL)API_DB_device_none_pwm_exist:(BOOL)state pwm:(int)pwm;
-(int)API_DB_device_connected_num;

-(void)API_DB_table_delete:(TABLE_DEVICE_TYPE)itemType uuid:(NSString*)uuid;
-(void)API_DB_table_show;

//注册侦听函数
-(void)API_register_BLE_callback:(id<BLECallback>)callback;
-(void)API_unregister_BLE_callback:(id<BLECallback>)callback;

-(BOOL)API_operate_device:(BLE_OPT_TYPE)optType uuid:(NSString*)uuid;
-(BOOL)API_send_data:(SEND_DATA_TYPE)sendType uuid:(NSString*)uuid data:(NSData*)data;
-(BOOL)API_send_data_fix1:(NSData*)data1 data2:(NSData*)data2;
-(Boolean)API_send_data_repeat:(NSString *)uuid data:(NSData *)data num:(int)num;
-(Boolean)API_set_bt_name:(NSString *)uuid name:(NSData *)name;
-(void)API_reset_queue;
-(void)API_set_delayMs:(float)delayMs;

-(int)API_get_max_links;
-(void)API_set_libType:(LIB_TYPE)libType;
-(Boolean)API_check_CentralManager_state;

-(void)API_set_timeout:(NSString *)uuid value:(NSString*)value;
-(NSString *)API_get_timeout:(NSString *)uuid;
-(void)set_service_uuid:(NSString *)uuid;
-(void)API_adv_info:(Byte *)data;
-(void)API_stop_adv;
-(void)API_save_log;

@end




