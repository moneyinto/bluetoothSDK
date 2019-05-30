//
//  TPGroup.h
//  meshLib
//
//  Created by yqf on 16/12/16.
//  Copyright © 2016年 Jonathan. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FMDTObject.h"

//保存组信息
@interface TPGroup : FMDTObject

@property (nonatomic, strong) NSString *homeId;//mesh网络的homeId

@property (nonatomic, assign) int groupId;//组id
@property (nonatomic, copy) NSString *groupName;//组名称

@property (nonatomic, assign) int nodes;//组中的设备个数
@property (nonatomic, assign) int flag;//是否为用户创建的组，区分网络中存在的组

@end
