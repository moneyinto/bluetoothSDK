//
//  PLSigMeshProvisionClient.h
//  sigmesh
//
//  Created by Zhang Jonathan on 2018/12/7.
//  Copyright © 2018年 Zhang Jonathan. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MeshNetInfo.h"
#import "MeshNodeInfo.h"

@protocol PLSigMeshProvisionCallback <NSObject>

@optional

-(void)onDeviceFoundUnprovisioned:(NSString *)uuid btAddr:(NSString *)btAddr rssi:(int)rssi;
-(void)onProvisionComplete:(int)result provision_node:(MeshNodeInfo *) provision_node mesh_net:(MeshNetInfo *)mesh_net;
-(void)onAdvProvisionComplete:(MeshNetInfo *)mesh_net;

@end

@interface PLSigMeshProvisionClient : NSObject

+(PLSigMeshProvisionClient *)getInstance;

-(void)connect:(NSString *)uuid;

-(void)initMesh:(MeshNetInfo *)net;
-(void)processEvent:(short)opcode data:(uint8_t *)data len:(int)len;

-(void)register_provision_callback:(id<PLSigMeshProvisionCallback>)callback;
-(void)unregister_provision_callback:(id<PLSigMeshProvisionCallback>)callback;
-(NSMutableArray *)provisionCallback;

@end

