//
//  TPScan.h
//  meshLib
//
//  Created by Zhang Jonathan on 2018/7/31.
//  Copyright © 2018年 Jonathan. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FMDTObject.h"


@interface TPScan : FMDTObject

@property (nonatomic, copy) NSString *uuid;     //设备identifier对应的uuid
@property (nonatomic, copy) NSString *btAddr;   //当前设备的蓝牙地址
@property (nonatomic, assign) int companyId;    //公司Id
@property (nonatomic, assign) int productId;    //产品Id
@property (nonatomic, assign) int rssi;         //信号强度

+(instancetype)initWithInfo:(NSString *)uuid;
+(instancetype)initWithInfo:(NSString *)uuid btAddr:(NSString *)btAddr productId:(int)productId;


@end
