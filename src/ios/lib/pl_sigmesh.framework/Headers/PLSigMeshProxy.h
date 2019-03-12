//
//  PLSigMeshProxy.h
//  sigmesh
//
//  Created by Zhang Jonathan on 2018/12/7.
//  Copyright © 2018年 Zhang Jonathan. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MeshNetInfo.h"
#import "MeshNodeInfo.h"

@protocol PLSigMeshProxyCallback <NSObject>

@optional

-(void)onConfigComplete:(int)result config_node:(MeshNodeInfo*)config_node mesh_net:(MeshNetInfo*)mesh_net;
-(void)onAddProgress:(int)result;

-(void)onDeviceFoundProxy:(NSString *)uuid rssi:(int)rssi dev_list_size:(int)dev_list_size;
-(void)onMeshStatus:(int)status addr:(NSString *)addr;
-(void)onDataReceived:(short)src op:(int)op data:(NSData *)data len:(int)len;

-(void)onOnOffChanged:(short)src onoff:(BOOL)onoff;
-(void)onLevelChanged:(short)src level:(short)level;
-(void)onPowerLevelChanged:(short)src level:(short)level;

-(void)onSubsChanged:(short)src status:(int)status ele_addr:(short)ele_addr subs_addr:(short)subs_addr vendor:(short)vendor model:(short)model;
-(void)onPubsChanged:(short)src status:(int)status ele_addr:(short)ele_addr pubs_addr:(short)pubs_addr vendor:(short)vendor model:(short)model;

-(void)onSceneStoreChanged:(short)src status:(int)status current:(short)current scene_list:(NSMutableArray *) scene_list;
-(void)onSceneChanged:(short)src status:(int)status current:(short)current;

-(void)onVersionGet:(short)src ver:(NSString *)ver;

-(void)onTestCounterGet:(short)src coutner:(int)coutner;

-(void)onVendorBtFuncStatus:(short)src status:(int)status data:(Byte *)data len:(int)len;
-(void)onNodeResetStatus:(short)src;

-(void)onVendorUartData:(short)src data:(NSData *)data len:(int)len;

-(void)onJiechangConfigStatus:(short)src data:(NSData *)data len:(int)len;

@end


@interface PLSigMeshProxy : NSObject

+(PLSigMeshProxy *)getInstance;

-(void)initMesh:(MeshNetInfo *)net;
-(void)joinMesh;
-(void)exitMesh;
-(void)processEvent:(short)opcode data:(uint8_t *)data len:(int) len;
-(void)startConfig:(MeshNodeInfo *)node;

-(void)register_proxy_callback:(id<PLSigMeshProxyCallback>)callback;
-(void)unregister_proxy_callback:(id<PLSigMeshProxyCallback>)callback;
-(NSMutableArray *)proxyCallback;

@end


