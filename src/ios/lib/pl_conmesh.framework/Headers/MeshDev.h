//
//  MeshDevice.h
//  conMesh
//
//  Created by Zhang Jonathan on 2019/4/26.
//  Copyright © 2019年 Zhang Jonathan. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>

NS_ASSUME_NONNULL_BEGIN

@interface MeshDev : NSObject

@property (strong, nonatomic) CBCentral *central;
@property (nonatomic, copy) NSString *uuid;
@property (nonatomic, assign) int device_type;


+(instancetype)initWithInfo:(NSString *)uuid device_type:(int)device_type;

@end

NS_ASSUME_NONNULL_END
