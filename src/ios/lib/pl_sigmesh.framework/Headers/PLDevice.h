//
//  PLDevice.h
//  bleCentral
//
//  Created by yqf on 17/4/6.
//  Copyright © 2017年 Jonathan. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FMDTObject.h"

//动态获取的设备信息
@interface PLDevice: FMDTObject

@property (nonatomic, copy) NSString *uuid;//设备当前的uuid
@property (nonatomic, copy) NSString *advUuid;//设备广播的device uuid
@property (nonatomic, copy) NSString *btAddr;//蓝牙地址
@property (nonatomic, copy) NSString *name;//蓝牙名称
@property (nonatomic, assign) int isChoose;//是否选择，不能用关键字select
@property (nonatomic, assign) int isConnected;//是否连接成功
@property (nonatomic, assign) int rssi;//设备的rssi
@property (nonatomic, assign) int flag; //标记设备是否为新设备，用于UI刷新
@property (nonatomic, assign) int provision;

@end
