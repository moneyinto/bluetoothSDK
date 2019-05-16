//
//  PLSigMeshService.h
//  sigmesh
//
//  Created by Zhang Jonathan on 2018/12/7.
//  Copyright © 2018年 Zhang Jonathan. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MJExtension.h"
#import "PLSigMeshConst.h"
#import "PLFileManager.h"
#import "MeshNetInfo.h"
#import "MeshNodeInfo.h"
#import "MeshElementInfo.h"
#import "AdminNodeInfo.h"
#import "PLSigMeshProxy.h"
#import "PLSigMeshProvisionClient.h"
#import "PLSigMeshModelMsg.h"

@interface PLSigMeshService : NSObject

+(PLSigMeshService *)getInstance;

-(void)chooseMeshNet:(MeshNetInfo *)mesh_net;
-(void)save_mesh_info:(MeshNetInfo *)mesh_net;
-(void)save_mesh_seq:(int)seq;
-(void)addMeshNet:(MeshNetInfo *)mesh_net;
-(NSMutableArray *)getMeshList;
-(void)process_event:(int)opcode len:(int)len data:(uint8_t *)data;
-(void)send_notify_message:(NSString*)msg data:(NSDictionary *)sendData;
-(void)configNode:(short)dst;
-(void)resetNode:(short)dst;
-(int)proxyJoin;
-(int)proxyExit;
-(int)get_node_from_eleaddr:(short)addr;
-(MeshNodeInfo *)getNodeByAddr:(short)addr;
-(MeshElementInfo *)getElementByAddr:(short)addr;
-(void)updateElementByAddr:(MeshElementInfo *)info addr:(short)addr;
-(void)delMeshNet:(NSString *)name;
-(void)startProvision:(NSString *)uuid ele_num:(Byte)ele_num;
-(int)advMultiProvision:(NSMutableArray *)provision_list;

//subs
-(int)addSubs:(short)dst subs_addr:(short)subs_addr company:(short)company model:(short)model;
-(int)delSubs:(short)dst subs_addr:(short)subs_addr company:(short)company model:(short) model;
//subs end

//onoff
-(int)getOnoff:(short)dst key_index:(int)key_index;
-(int)setOnoff:(short)dst onoff:(Byte)onoff transitiontime:(Byte)transitiontime delay:(Byte)delay key_index:(int)key_index ack:(BOOL)ack;
//onooff end

//level
-(int)getLevel:(short)dst appkeyidx:(int)appkeyidx;
-(int)setLevel:(short)dst level:(short)level transitionTime:(Byte) transitionTime delay:(Byte)delay appkeyidx:(int)appkeyidx ack:(BOOL)ack;
-(int)setLevelDelta:(short)dst delta:(int)delta transitiontime:(Byte) transitiontime delay:(Byte)delay key_index:(int)key_index ack:(BOOL)ack;
-(int)setPowerLevel:(short)dst level:(short)level transitionTime:(Byte) transitionTime delay:(Byte)delay appkeyidx:(int)appkeyidx ack:(BOOL)ack;
-(int)getPowerLevel:(short)dst appkeyidx:(int)appkeyidx;
//level end

//scene
-(int)addScene:(short)dst scene_number:(short)scene_number appkeyidx:(int) appkeyidx;
-(int)delScene:(short)dst scene_number:(short)scene_number appkeyidx:(int)appkeyidx;
-(int)recallScene:(short)dst scene_number:(short)scene_number transitiontime:(Byte)transitiontime delay:(Byte)delay appkeyidx:(int)appkeyidx ack:(BOOL)ack;
-(int)getSceneList:(short)dst appkeyidx:(int)appkeyidx;
//scene end

//vendor func
-(int)getVendorVersionCommon:(short)dst appkeyidx:(int)appkeyidx;
-(int)enableVendorDemoCounter:(short)dst enable:(Byte)enable appkeyidx:(int)appkeyidx;
-(int)getVendorDemoCounter:(short)dst appkeyidx:(int)appkeyidx;
-(int)toggleVendorOnoff:(short)dst appkeyidx:(int)appkeyidx ack:(BOOL)ack;
-(int)toggleVendorLevel:(short)dst delta:(int)delta appkeyidx:(int)appkeyidx ack:(BOOL)ack;
-(int)setVendorFunc:(short)dst target_addr:(short)target_addr index:(Byte)index func:(Byte)func para:(int)para appkeyidx:(int)appkeyidx;
-(int)stopCurtain:(short)dst appkeyidx:(int)appkeyidx;
-(int)changeCurtainDirection:(short)dst appkeyidx:(int)appkeyidx;
-(int)vendorLevelDelta:(short)dst delta:(short)delta appkeyidx:(int)appkeyidx;
-(int)vendorUartSend:(short)dst data:(uint8_t *)data len:(int)len appkeyidx:(int)appkeyidx;

-(int)vendorJiechangConfigSet:(short)dst enable:(uint8_t)enable total_addr:(short)total_addr node_interval:(int)node_interval round_interval:(int)round_interval appkeyidx:(int)appkeyidx;
-(int)vendorJiechangConfigGet:(short)dst appkeyidx:(int)appkeyidx;
//vendor end


-(int)getNodeLastAddr;
-(BOOL)addAdminNode:(NSString *)fileName;
-(NSString *)getIPAddress;
-(void)test;
@property (nonatomic, assign) int admin_index;
@property (nonatomic, copy) NSString *current_admin;
-(NSString *)getJsonStrMeshNet:(int)index;
-(int)updateJsonStrMeshNet:(NSString *)meshinfo;

@end
