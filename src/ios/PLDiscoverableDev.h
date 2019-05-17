//
//  PLUnProvisionDev.h
//  sigmesh
//
//  Created by Zhang Jonathan on 2018/12/13.
//  Copyright © 2018年 Zhang Jonathan. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <pl_conmesh/TPScan.h>

@interface PLDiscoverableDev : NSObject

@property (nonatomic, copy) NSString *uuid;//设备当前的uuid
@property (nonatomic, copy) NSString *btAddr;//蓝牙地址
@property (nonatomic, assign) BOOL isCheck;//是否选择，不能用关键字select

+(instancetype)initWithInfo:(TPScan *)device;

@end
