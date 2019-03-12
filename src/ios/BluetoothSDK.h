//
//  BluetoothSDK.h
//  helloWorld
//
//  Created by 钱进 on 2019/3/11.
//

#import <Foundation/Foundation.h>
#import <Cordova/CDVPlugin.h>
#import <pl_sigmesh/PLSigMeshService.h>
#import <pl_sigmesh/BLEDeviceManager.h>

NS_ASSUME_NONNULL_BEGIN

@interface BluetoothSDK : CDVPlugin <PLSigMeshProxyCallback, PLSigMeshProvisionCallback> {
    CDVInvokedUrlCommand *RegisterWifiCommand;
    CDVInvokedUrlCommand *AddDeviceCommand;
}

@property (nonatomic, assign) int device_addr;

@end

NS_ASSUME_NONNULL_END