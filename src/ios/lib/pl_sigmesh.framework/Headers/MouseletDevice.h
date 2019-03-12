//
//  MouseletDevice.h
//  Lamps
//
//  Created by yqf on 16/3/23.
//  Copyright © 2016年 jerryDing. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>

@interface MouseletDevice : NSObject

@property (atomic) CBPeripheral  *gPeripheral;
@property (nonatomic, copy) NSString *gName;

@property (atomic) NSUUID        *gIdentifier;
@property (atomic) NSString      *gIdentity;
@property (nonatomic, assign) int rssi;
@property (nonatomic, assign) int provision;
@property (nonatomic, copy) NSString *btAddr;
@property (nonatomic, copy) NSString *advUuid;

@property (atomic, strong) CBCharacteristic     *gCharacteristic_write;
@property (atomic, strong) CBCharacteristic     *gCharacteristic_notify;
@property (atomic, strong) CBCharacteristic     *gCharacteristic_BT_name;

@end
