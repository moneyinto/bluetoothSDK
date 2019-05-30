//
//  TPMesh.h
//  office
//
//  Created by yqf on 16/9/12.
//  Copyright © 2016年 Jonathan. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FMDTObject.h"

//保存mesh网络信息
@interface TPMesh : FMDTObject

@property (nonatomic, strong) NSString *meshName;//mesh网络的名称
@property (nonatomic, strong) NSString *tag;//mesh网络的tag
@property (nonatomic, strong) NSString *homeId;//mesh网络的homeId
@property (nonatomic, strong) NSString *pwd;//mesh网络的密码
@property (nonatomic, assign) int rssi;

//mesh中的最大组号，创建组时需要该信息
@property (nonatomic, assign) int maxGroupId;

@property (nonatomic, assign) int ctlGroupId;//当前控制的组
@property (nonatomic, assign) int configGroupId;//当前配置的组
@property (nonatomic, assign) int sceneId;//当前选择的场景Id
@property (nonatomic, assign) int productId;//当前选择的产品Id

@property (nonatomic, assign) int ctlGroupUpdate;//当前控制的组是否需要刷新
@property (nonatomic, assign) int sceneUpdate; //当前选中的scene是否需要刷新
@property (nonatomic, assign) int productUpdate;//当前选择的产品是否需要刷新

@end
