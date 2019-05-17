//
//  BluetoothSDK.h
//  helloWorld
//
//  Created by 钱进 on 2019/3/11.
//

#import <Foundation/Foundation.h>
#import <Cordova/CDVPlugin.h>
#import <pl_conmesh/MeshService.h>
#import <pl_conmesh/BleUtil.h>
#import "PLDiscoverableDev.h"

NS_ASSUME_NONNULL_BEGIN

@interface BluetoothSDK : CDVPlugin <MeshCallback> {
    CDVInvokedUrlCommand *RegisterWifiCommand;
    CDVInvokedUrlCommand *ListenerWifiJoinStatusCommand;
    CDVInvokedUrlCommand *ScanDeviceCommand;
    CDVInvokedUrlCommand *AddDeviceCommand;
    CDVInvokedUrlCommand *DeleteDeviceCommand;
    NSMutableArray *ScanDeviceList;
}

@end

NS_ASSUME_NONNULL_END
