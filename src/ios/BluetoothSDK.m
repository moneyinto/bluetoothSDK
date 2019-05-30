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
    ListenerWifiJoinStatusCommand = nil;
    ScanDeviceCommand = nil;
    AddDeviceCommand = nil;
    DeleteDeviceCommand = nil;
    ScanDeviceList = [NSMutableArray array];
}

// wifi监听回调
-(void)on_homeId_found:(NSString *)homeId{
    NSLog(@"=== on_homeId_found: %@", homeId);
    NSArray* wifiList = [[MeshService getInstance] API_DB_mesh_get_list:NO];
    for (int i=0; i<[wifiList count]; i++) {
        TPMesh* wifi = [wifiList objectAtIndex:i];
        if (wifi.homeId == homeId) {
            NSString *meshName = @"";
            if([wifi.meshName containsString:@"m_"]){
                meshName = [wifi.meshName substringFromIndex:2];
            }
            NSDictionary *response = @{@"wifiId": homeId, @"wifiName": meshName};
            [self keepCallback:RegisterWifiCommand response:response];
        }
    }
}

-(void)on_device_num_changed:(int)current all:(int)all{
    NSLog(@"on_device_num_changed: %02d/%02d", current, all);
    
    if(current == all){
        NSDictionary *response = @{@"status": @8};
        [self keepCallback:ListenerWifiJoinStatusCommand response:response];
    }
}

-(void)on_connection_state_changed:(BOOL)state{
    NSLog(@"on_connection_state_changed: %d", state);
    NSDictionary *response = nil;
    if (state) {
        response = @{@"status": @3};
    } else {
        response = @{@"status": @5};
    }
    [self keepCallback:ListenerWifiJoinStatusCommand response:response];
}

-(void)on_mesh_status_changed:(NSString *)uuid status:(int)status{
    NSDictionary *response = nil;
    switch (status) {
        case MeshStatusWrongPwd:
            response = @{@"status": @9};
            NSLog(@"mesh status: password wrong");
            break;
        case MeshStatusWelcome:
            response = @{@"status": @6};
            NSLog(@"mesh status: welcome");
            break;
        default:
            break;
    }
    [self keepCallback:ListenerWifiJoinStatusCommand response: response];
}

-(void)on_update_device_list{
    NSLog(@"on_update_device_list");
//    if([[MeshService getInstance] API_get_connection_status]){
//        [self loadDevList];
//    }
    [self keepCallback:ListenerWifiJoinStatusCommand response:@{@"status": @8}];
}

-(void)onGroupStatus:(Byte)srcType addr:(Byte *)addr status:(Byte)status groupId:(Byte)groupId deviceBean:(DeviceBean *)deviceBean{
    NSLog(@"onGroupStatus scrType: %d, addr: %@, status: %d, groupId: %d, deviceBan: %@", srcType, [BleUtil byte2HexStr:addr len:4], status, groupId, deviceBean);
    
}

-(void)onNameChanged:(Byte)srcType addr:(Byte *)addr status:(Byte)status name:(NSString *)name{
    NSLog(@"onNameChanged srcType: %d, addr: %@, status: %d, name: %@", srcType, [BleUtil byte2HexStr:addr len:4], status, name);
}

-(void)onDeviceExited:(Byte)srcType addr:(Byte *)addr status:(Byte)status{
    NSLog(@"onDeviceExited srcType: %d, addr: %@, status: %d", srcType, [BleUtil byte2HexStr:addr len:4], status);
}

-(void)onDeviceDeleted:(Byte)srcType addr:(Byte *)addr status:(Byte)status{
    NSLog(@"onDeviceDeleted srcType: %d, addr: %@, status: %d", srcType, [BleUtil byte2HexStr:addr len:4], status);
    [self callback:DeleteDeviceCommand response:nil];
}

-(void)onDeviceRebooted:(Byte)srcType addr:(Byte *)addr{
    NSLog(@"onDeviceRebooted srcType: %d, addr: %@", srcType, [BleUtil byte2HexStr:addr len:4]);
}

-(void)onSceneRegStoreStatus:(Byte)srcType addr:(Byte *)addr unitIndex:(Byte)unitIndex status:(Byte)status sceneId:(Byte)sceneId{
    NSLog(@"onSceneRecallStatus srcType: %d, addr: %@ unitIndex: %d, status: %d, sceneId: %d", srcType, [BleUtil byte2HexStr:addr len:4], unitIndex, status, sceneId);
}

-(void)onSceneRecallStatus:(Byte)srcType addr:(Byte *)addr unitIndex:(Byte)unitIndex status:(Byte)status sceneId:(Byte)sceneId{
    NSLog(@"onSceneRecallStatus srcType: %d, addr: %@ unitIndex: %d, status: %d, sceneId: %d", srcType, [BleUtil byte2HexStr:addr len:4], unitIndex, status, sceneId);
//    [self loadDevList];
}

-(void)on_discoverable_device_found:(TPScan *)scanDevice{
    NSLog(@"on_discoverable_device_found: %@", scanDevice);
    NSDictionary *response = @{@"device": scanDevice.btAddr};
    BOOL isExit = false;
    PLDiscoverableDev *dev = nil;
    if(nil != scanDevice){
        for (int i=0; i<[ScanDeviceList count]; i++) {
            dev = [PLDiscoverableDev initWithInfo:ScanDeviceList[i]];
            if ([dev.btAddr isEqual:scanDevice.btAddr]) {
                isExit = true;
            }
        }
        if (!isExit) {
            [ScanDeviceList addObject:scanDevice];
        }
    }
    [self keepCallback:ScanDeviceCommand response:response];
}

// 命令回调
-(void)on_recv_mesh_data:(Byte)channel data:(NSData *)data broadcast_flag:(BOOL)broadcast_flag{
    NSLog(@"on_recv_mesh_data channel: %x, data: %@, broadcast_flag: %d", channel, data, broadcast_flag);
}

// 添加设备回调
-(void)on_device_add_status:(NSString *)uuid status:(int)status{
     switch (status) {
        case ADD_DEVICE_NONE:
            
            break;
        case ADD_DEVICE_START:
            
            break;
        case ADD_DEVICE_PROCESS:
            
            break;
        case ADD_DEVICE_OK:
            [self callback:AddDeviceCommand response:nil];
            break;
        case ADD_DEVICE_FAILED:
            
            break;
        default:
            break;
    }
}

// init
- (void)init:(CDVInvokedUrlCommand*)command
{
    [[MeshService getInstance] API_register_mesh_data_callback:self];
    [self callback:command response:nil];
}

// 扫描wifi
- (void)scanWifi:(CDVInvokedUrlCommand*)command
{
    NSString* isEnable = [command argumentAtIndex:0];
    BOOL isOK = [isEnable boolValue];
    if (isOK) {
        [[MeshService getInstance] API_start_scan];
    } else {
        [[MeshService getInstance] API_stop_scan];
    }
    [self callback:command response:nil];
}

// 获取wifi列表
- (void)getWifiNetIds:(CDVInvokedUrlCommand*)command
{
    RegisterWifiCommand = command;
}

// 创建蓝牙网络
- (void)createOrLoginWifi:(CDVInvokedUrlCommand*)command
{
    NSString* wifi = [command.arguments objectAtIndex:0];
    NSString* password = [command.arguments objectAtIndex:1];
    if(4 != wifi.length || 4 != password.length){
        return;
    }
    
    int rssi = [[MeshService getInstance] API_get_rssi:wifi];
    NSString* name = [[MeshService getInstance] API_get_mesh_name:wifi];
    [[MeshService getInstance] API_set_mesh_info:name homeId:wifi pwd:password rssi:rssi];
    [self callback:command response:nil];
}

//获取wifi下设备列表
- (void)getWifiDeviceList:(CDVInvokedUrlCommand*)command
{
    NSArray* devices = [[MeshService getInstance] API_DB_device_get_list:NO];
    NSMutableArray *deviceList = [NSMutableArray array];
    for (int i=0; i<[devices count]; i++) {
        TPDevice *deviceTmp = [devices objectAtIndex:i];
        NSString *nameTmp = deviceTmp.deviceName;
        if (nameTmp == nil) nameTmp = @"";
        NSDictionary *device = @{@"btAddrStr": deviceTmp.btAddr, @"deviceName": nameTmp};
        [deviceList addObject:device];
    }
    [self callback:command response:@{@"deviceList": deviceList}];
}

// 状态监听
- (void)listenerWifiJoinStatus:(CDVInvokedUrlCommand*)command
{
    ListenerWifiJoinStatusCommand = command;
}

// joinMesh
- (void)joinMesh:(CDVInvokedUrlCommand*)command
{
    [[MeshService getInstance] API_join_mesh];
    [self callback:command response:nil];
}

// exitMesh
- (void)exitMesh:(CDVInvokedUrlCommand*)command
{
    [[MeshService getInstance] API_exit_mesh];
    [self callback:command response:nil];
}

// pingAll
- (void)pingMesh:(CDVInvokedUrlCommand*)command
{
    [[MeshService getInstance] pingAll];
    [self callback:command response:nil];
}

// 开始扫描蓝牙设备
- (void)scanDevice:(CDVInvokedUrlCommand*)command
{
    NSString* isEnable = [command argumentAtIndex:0];
    BOOL isOK = [isEnable boolValue];
    if (isOK) {
        [ScanDeviceList removeAllObjects];
        [[MeshService getInstance] API_start_scan];
        ScanDeviceCommand = command;
    } else {
        [[MeshService getInstance] API_stop_scan];
        [self callback:command response:nil];
    }
}

// 删除设备
- (void)deleteDevice:(CDVInvokedUrlCommand*)command
{
    NSString* btAddr = [command argumentAtIndex:0];
    TPDevice* device = [self getDeviceByBtAddr:btAddr];
    Byte vAddr[4] = {0};
    [BleUtil int2byteArray:device.vAddr data:vAddr];
    [[MeshService getInstance] deleteDevice:vAddr];
    DeleteDeviceCommand = command;
}

// 添加蓝牙设备到网络
- (void)addDevice:(CDVInvokedUrlCommand*)command
{
    NSString* btAddr = [command argumentAtIndex:0];
    for (int i=0; i<[ScanDeviceList count]; i++) {
        PLDiscoverableDev* deviceTmp = [ScanDeviceList objectAtIndex:i];
        if ([deviceTmp.btAddr isEqual:btAddr]) {
            [[MeshService getInstance] API_add_device:deviceTmp.uuid];
            AddDeviceCommand = command;
        }
    }
}

// 向设备发送命令
- (void)sendCommand:(CDVInvokedUrlCommand*)command
{
    CDVPluginResult* pluginResult = nil;
    NSString *btAddr = [command.arguments objectAtIndex:0];
    NSString *info = [command.arguments objectAtIndex:1];
    TPDevice* device = [self getDeviceByBtAddr:btAddr];
    if(![info isEqual:@""]){
        NSData *temp = [BleUtil hexStringToData:info];
        Byte *data = (Byte*)[temp bytes];
        Byte vAddr[4] = {0};
        [BleUtil int2byteArray:device.vAddr data:vAddr];
        [[MeshService getInstance] vendorSend:vAddr unitIndex:UNIT0 vendorOp:(short)0 data:data len:(int)temp.length];
    }
    
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)rename:(CDVInvokedUrlCommand*)command
{
    CDVPluginResult* pluginResult = nil;
    NSString *btAddr = [command.arguments objectAtIndex:0];
    NSString *name = [command.arguments objectAtIndex:1];
    TPDevice* device = [self getDeviceByBtAddr:btAddr];
    NSString* tempName = [@"m_" stringByAppendingString:name];
    NSData* tmpData = [tempName dataUsingEncoding:NSUTF8StringEncoding];
    Byte *data = (Byte *)[tmpData bytes];
    Byte vAddr[4] = {0};
    [BleUtil int2byteArray:device.vAddr data:vAddr];
//    [[MeshService getInstance] nameSet:vAddr data:data len:(int)tmpData.length ackType:ACK_TYPE_REMOTE];
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

-(TPDevice*)getDeviceByBtAddr:(NSString*)btAddr
{
    NSArray* devices = [[MeshService getInstance] API_DB_device_get_list:NO];
    TPDevice* device = nil;
    for (int i=0; i<[devices count]; i++) {
        TPDevice* deviceTmp = [devices objectAtIndex:i];
        if ([deviceTmp.btAddr isEqual:btAddr]) {
            device = deviceTmp;
        }
    }
    return device;
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
