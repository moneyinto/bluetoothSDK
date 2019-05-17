//
//  UnitInfo.h
//  pl_conmesh
//
//  Created by Zhang Jonathan on 2019/5/7.
//  Copyright © 2019年 Zhang Jonathan. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface UnitInfo : NSObject

@property (nonatomic, strong) NSMutableArray *groupList;
@property (nonatomic, assign) int functionId;
@property (nonatomic, assign) BOOL onoff;
@property (nonatomic, assign) int level;

@end

NS_ASSUME_NONNULL_END
