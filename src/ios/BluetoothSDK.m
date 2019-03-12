//
//  BluetoothSDK.m
//  helloWorld
//
//  Created by 钱进 on 2019/3/11.
//

#import "BluetoothSDK.h"

@implementation BluetoothSDK

- (void)pluginInitialize {
    [super pluginInitialize];
    RegisterWifiCommand = nil;
    AddDeviceCommand = nil;
}

// 创建蓝牙网络
- (void)createWifi:(CDVInvokedUrlCommand*)command
{
    CDVPluginResult* pluginResult = nil;
    NSString* wifi = [command.arguments objectAtIndex:0];

    NSString *netKey = [wifi substringToIndex:4];
    NSString *appKey = [wifi substringFromIndex:4];

    MeshNetInfo *meshNetInfo = [MeshNetInfo initWithInfo:netKey appKey:appKey];
    [[PLSigMeshService getInstance] addMeshNet:meshNetInfo];

    [[PLSigMeshService getInstance] send_notify_message:NOTIFY_REFRESH_NET_LIST data:nil];
    // if (echo != nil && [echo length] > 0) {
    //     pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:echo];
    // } else {
    //     pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
    // }
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];

    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

// 获取蓝牙网络id
- (void)getWifiNetIds:(CDVInvokedUrlCommand*)command
{
    CDVPluginResult* pluginResult = nil;
    NSArray *netIds = [NSArray arrayWithArray:[[PLSigMeshService getInstance] getMeshList]];
    NSDictionary *response = @{@"netIds": netIds};
    
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary: response];

    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

// 注册获取蓝牙设备监听
- (void)registerScanDevices:(CDVInvokedUrlCommand*)command
{
    [[PLSigMeshProvisionClient getInstance] register_provision_callback:self];
    RegisterWifiCommand = command;
}

// 取消注册获取蓝牙设备监听
- (void)unRegisterScanDevices:(CDVInvokedUrlCommand*)command
{
    CDVPluginResult* pluginResult = nil;
    [[PLSigMeshProvisionClient getInstance] unregister_provision_callback:self];
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

// 注册获取蓝牙设备回调
- (void)onDeviceFoundUnprovisioned:(NSString *)uuid btAddr:(NSString *)btAddr rssi:(int)rssi{
    NSLog(@"onDeviceFoundUnprovisioned uuid: %@, btAddr: %@, rssi: %d", uuid, btAddr, rssi);

    CDVPluginResult* pluginResult = nil;
    NSArray *devices = [[BLEDeviceManager getInstance]API_DB_device_get_items:TABLE_DEVICE_PROVISION uuid:nil];
    NSDictionary *response = @{@"devices": devices, @"btAddr": btAddr};
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary: response];
    [pluginResult setKeepCallbackAsBool:TRUE];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:RegisterWifiCommand.callbackId];
}

// 开始扫描蓝牙设备
- (void)startScanDevice:(CDVInvokedUrlCommand*)command
{
    CDVPluginResult* pluginResult = nil;
    [[BLEDeviceManager getInstance]API_start_scan];
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

// 添加蓝牙设备到网络
- (void)addDevice:(CDVInvokedUrlCommand*)command
{
    AddDeviceCommand = command;
    NSString *uuid = [command.arguments objectAtIndex:0];
    Byte info[18] = {0};
    [BleUtil hexStr2Byte:uuid data:info];
    [[PLSigMeshService getInstance] startProvision:uuid ele_num:info[15]];
    [[PLSigMeshService getInstance] send_notify_message:NOTIFY_ADDING_NODE data:nil];
}

// 注册添加设备进程监听
- (void)registerAddProgress:(CDVInvokedUrlCommand*)command
{
    CDVPluginResult* pluginResult = nil;
    [[PLSigMeshProxy getInstance]register_proxy_callback:self];
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

// 取消注册添加设备进程监听
- (void)unRegisterAddProgress:(CDVInvokedUrlCommand*)command
{
    CDVPluginResult* pluginResult = nil;
    [[PLSigMeshProxy getInstance]unregister_proxy_callback:self];
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

// 注册添加设备进程回调
- (void)onAddProgress:(int)result{
    NSString *info = @"";
    NSString *value = @"0";
    switch (result) {
        case MESH_EVT_PROVISON_CAPABITIES:
            info = @"Provisioning...";
            value = @"10";
            break;
        case MESH_EVT_PROVISON_DEV_KEY:
            info = @"Provisioning...";
            value = @"30";
            break;
        case MESH_EVT_PROVISON_COMPLETE:
            info = @"Provision ok";
            value = @"50";
            break;
        case MESH_EVT_PROVISON_FAIL:
            info = @"Provision failed";
            value = @"50";
            break;
        case MESH_EVT_CONFIG_OK:
            info = @"Add OK";
            value = @"100";
            break;
        case MESH_EVT_CONFIG_FAIL:
            info = @"Add failed";
             value = @"85";
            break;
        case MESH_EVT_COMPOS_DATA_GET:
            info = @"Configing...";
            value = @"75";
            break;
        default:
            break;
    }
    CDVPluginResult* pluginResult = nil;
    NSDictionary *response = @{@"info": info, @"value": value};
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary: response];
    [pluginResult setKeepCallbackAsBool:TRUE];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:AddDeviceCommand.callbackId];
}

// 向设备发送命令
- (void)sendCommand:(CDVInvokedUrlCommand*)command
{
    CDVPluginResult* pluginResult = nil;
    NSString *info = [command.arguments objectAtIndex:0];;
    if(![info isEqual:@""]){
        NSData *temp = [BleUtil hexStringToData:info];
        Byte *data = (Byte*)[temp bytes];

        [[PLSigMeshService getInstance] vendorUartSend:_device_addr data:data len:(int)[temp length] appkeyidx:PL_DEFAULT_APP_KEY_INDEX];
    }
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

@end
