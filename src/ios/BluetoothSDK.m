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
    MeshListenerCommand = nil;
    netWifiList = @[];
}

// 创建蓝牙网络
- (void)createWifi:(CDVInvokedUrlCommand*)command
{
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
    [self callback:command response:nil];
}

// 删除蓝牙网络
- (void)deleteWifiNetId:(CDVInvokedUrlCommand*)command
{
    NSString *index = [command.arguments objectAtIndex:0];
    int n = [index intValue];
    MeshNetInfo *_mesh_net = [netWifiList objectAtIndex:n];
    [[PLSigMeshService getInstance] delMeshNet:_mesh_net.name];
}

// 获取蓝牙网络id
- (void)getWifiNetIds:(CDVInvokedUrlCommand*)command
{
    NSArray *netIds = [NSArray arrayWithArray:[[PLSigMeshService getInstance] getMeshList]];
    netWifiList = netIds;
    NSMutableArray *tmp_mesh_list = [NSMutableArray array];
    
    for (MeshNetInfo* item in netIds) {
        NSDictionary *netId = @{@"name": item.name, @"appKey": item.appkey, @"netKey": item.netkey};
        [tmp_mesh_list addObject:netId];
    };
    
    NSDictionary *response = @{@"netIds": tmp_mesh_list, @"success": @true};
    
    [self callback:command response:response];
}

// 选择蓝牙网络
- (void)chooseWifiNetId:(CDVInvokedUrlCommand*)command
{
    NSString *index = [command.arguments objectAtIndex:0];
    int n = [index intValue];
    MeshNetInfo *_mesh_net = [netWifiList objectAtIndex:n];
    [[PLSigMeshService getInstance] chooseMeshNet:_mesh_net];
    [self callback:command response:nil];

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
    RegisterWifiCommand = nil;
    [[PLSigMeshProvisionClient getInstance] unregister_provision_callback:self];
    [self callback:command response:nil];
}

// 注册获取蓝牙设备回调
- (void)onDeviceFoundUnprovisioned:(NSString *)uuid btAddr:(NSString *)btAddr rssi:(int)rssi{
    NSLog(@"onDeviceFoundUnprovisioned uuid: %@, btAddr: %@, rssi: %d", uuid, btAddr, rssi);

    NSArray *data = [[BLEDeviceManager getInstance]API_DB_device_get_items:TABLE_DEVICE_PROVISION uuid:nil];
    NSMutableArray *devices = [NSMutableArray array];
    for (PLDevice* item in data) {
        NSDictionary *device = @{@"name": item.name, @"address": item.btAddr, @"uuid": item.uuid};
        [devices addObject:device];
    }
    
    NSDictionary *response = @{@"devices": devices};
    
    [self keepCallback:RegisterWifiCommand response:response];
}

// 开始扫描蓝牙设备
- (void)scanDevice:(CDVInvokedUrlCommand*)command
{
    [[BLEDeviceManager getInstance]API_start_scan];
    [self callback:command response:nil];
}

// 添加蓝牙设备到网络
- (void)addDevice:(CDVInvokedUrlCommand*)command
{
    NSString *uuid = [command.arguments objectAtIndex:0];
    Byte info[18] = {0};
    [BleUtil hexStr2Byte:uuid data:info];
    [[PLSigMeshService getInstance] startProvision:uuid ele_num:info[15]];
    AddDeviceCommand = command;
}

// 注册添加设备进程监听
- (void)registerAddProgress:(CDVInvokedUrlCommand*)command
{
    [[PLSigMeshProxy getInstance]register_proxy_callback:self];
    [self callback:command response:nil];
}

// 取消注册添加设备进程监听
- (void)unRegisterAddProgress:(CDVInvokedUrlCommand*)command
{
    AddDeviceCommand = nil;
    [[PLSigMeshProxy getInstance]unregister_proxy_callback:self];
    [self callback:command response:nil];
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
    
    NSDictionary *response = @{@"info": info, @"progress": value};
    [self keepCallback:AddDeviceCommand response:response];
}

- (void)getDeviceList:(CDVInvokedUrlCommand*)command
{
    NSString *index = [command.arguments objectAtIndex:0];
    int n = [index intValue];
    NSMutableArray *deviceList = [NSMutableArray array];
    MeshNetInfo *_mesh_net = [netWifiList objectAtIndex:n];
    for (int i=0; i<[_mesh_net.nodes count]; i++) {
        MeshNodeInfo *model = [MeshNodeInfo mj_objectWithKeyValues:_mesh_net.nodes[i]];
        NSDictionary *device = @{@"name": model.name, @"uuid": model.uuid, @"version": model.version, @"addr": [NSNumber numberWithShort:model.primary_addr]};
        [deviceList addObject:device];
    }
    [self callback:command response:@{@"deviceList": deviceList}];
}

// 解绑删除设备
- (void)deleteDevice:(CDVInvokedUrlCommand*)command
{
    NSString *n = [command.arguments objectAtIndex:0];
    short addr = [n intValue];
    [[PLSigMeshService getInstance] resetNode:addr];
    [self callback:command response:nil];
}

// 强制删除设备
- (void)forceDeleteDevice:(CDVInvokedUrlCommand*)command
{
    NSString *n = [command.arguments objectAtIndex:0];
    short addr = [n intValue];
    [[PLSigMeshService getInstance] resetNode:addr];
    [self callback:command response:nil];
}

// 加入设备
- (void)proxyJoin:(CDVInvokedUrlCommand*)command
{
    [[PLSigMeshService getInstance]proxyJoin];
    [self callback:command response:nil];
}

// 退出设备
- (void)proxyExit:(CDVInvokedUrlCommand*)command
{
    [[PLSigMeshService getInstance]proxyExit];
    [self callback:command response:nil];
}

// 设备状态回调
-(void)onMeshStatus:(int)status addr:(NSString *)addr{
    NSLog(@"onMeshStatus: %d", status);
    switch (status) {
        case PL_MESH_EXIT:
            NSLog(@"-----------------");
//            [[PLSigMeshService getInstance]proxyJoin];
            [self keepCallback:MeshListenerCommand response:@{@"status": @2}];
            break;
        case PL_MESH_JOINING:
            // joining
            [self keepCallback:MeshListenerCommand response:@{@"status": @1}];
            break;
        case PL_MESH_JOINED:
            // join ok
            [self keepCallback:MeshListenerCommand response:@{@"status": @0}];
            break;
        default:
            break;
    }
}

- (void)onLight:(CDVInvokedUrlCommand*)command
{
    NSString *n = [command.arguments objectAtIndex:0];
    short addr = [n intValue];
    [[PLSigMeshService getInstance] setOnoff:addr onoff:1 transitiontime:PL_DEFAULT_ONOFF_TRANSITIONTIME delay:PL_DEFAULT_ONOFF_DELAY key_index:PL_DEFAULT_APP_KEY_INDEX ack:NO];
    [self callback:command response:nil];
}

- (void)offLight:(CDVInvokedUrlCommand*)command
{
    NSString *n = [command.arguments objectAtIndex:0];
    short addr = [n intValue];
    [[PLSigMeshService getInstance] setOnoff:addr onoff:0 transitiontime:PL_DEFAULT_ONOFF_TRANSITIONTIME delay:PL_DEFAULT_ONOFF_DELAY key_index:PL_DEFAULT_APP_KEY_INDEX ack:NO];
    [self callback:command response:nil];
}

// 向设备发送命令
- (void)sendCommand:(CDVInvokedUrlCommand*)command
{
    CDVPluginResult* pluginResult = nil;
    NSString *n = [command.arguments objectAtIndex:0];
    short addr = [n intValue];
    NSString *info = [command.arguments objectAtIndex:1];
    if(![info isEqual:@""]){
        NSData *temp = [BleUtil hexStringToData:info];
        Byte *data = (Byte*)[temp bytes];

        [[PLSigMeshService getInstance] vendorUartSend:addr data:data len:(int)[temp length] appkeyidx:PL_DEFAULT_APP_KEY_INDEX];
    }
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)getWifiJson:(CDVInvokedUrlCommand*)command
{
    NSString *n = [command.arguments objectAtIndex:0];
    int index = [n intValue];
    NSString *jsonString = [[PLSigMeshService getInstance] getJsonStrMeshNet:index];
    [self callback:command response:@{@"json": jsonString}];
}

- (void)updateWifiJson:(CDVInvokedUrlCommand*)command
{
    NSString *JsonString = [command.arguments objectAtIndex:0];
    [[PLSigMeshService getInstance] updateJsonStrMeshNet:JsonString];
    [self callback:command response:nil];
}

// 网络设备监听回调
- (void)wifiListener:(CDVInvokedUrlCommand*)command
{
    MeshListenerCommand = command;
}

-(void)callback:(CDVInvokedUrlCommand *) command response:(NSDictionary *) response
{
    CDVPluginResult *pluginResult = nil;
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary: response];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

-(void)keepCallback:(CDVInvokedUrlCommand *) command response:(NSDictionary *) response
{
    CDVPluginResult *pluginResult = nil;
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary: response];
    [pluginResult setKeepCallbackAsBool:TRUE];
    //通过cordova框架中的callBackID回调至JS的回调函数上
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

@end
