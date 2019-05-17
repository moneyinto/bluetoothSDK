//
//  DeviceBean.h
//  pl_conmesh
//
//  Created by Zhang Jonathan on 2019/5/8.
//  Copyright © 2019年 Zhang Jonathan. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TPDevice.h"

NS_ASSUME_NONNULL_BEGIN

@interface DeviceBean : NSObject

@property (nonatomic, copy) NSString *btAddr;
@property (nonatomic, assign) int vAddr;
@property (nonatomic, assign) int unitNum;
@property (nonatomic, strong) NSMutableArray *unitInfoList;

+(instancetype)initWithInfo:(TPDevice *)device;

@end

NS_ASSUME_NONNULL_END
