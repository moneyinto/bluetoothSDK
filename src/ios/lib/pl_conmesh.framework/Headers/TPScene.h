//
//  TPGroupScene.h
//  meshLib
//
//  Created by yqf on 17/3/21.
//  Copyright © 2017年 Jonathan. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FMDTObject.h"

//场景无法对组进行设置，它只能对全部进行控制或者单灯进行控制
//目前的接口：
//全部场景控制
//-(BOOL)API_CMD_scene_play:(int)group_id scene:(int)scene_id all:(BOOL)isAll
//单灯场景控制
//-(BOOL)API_CMD_scene_play:(int)vAddr sceneId:(int)sceneId
@interface TPScene:FMDTObject

@property (nonatomic, strong) NSString *homeId;//mesh网络的homeId

@property (nonatomic, assign) int sceneId;//场景id
@property (nonatomic, copy) NSString *sceneName;//场景名称

@end
