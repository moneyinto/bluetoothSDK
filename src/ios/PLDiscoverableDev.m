//
//  PLUnProvisionDev.m
//  sigmesh
//
//  Created by Zhang Jonathan on 2018/12/13.
//  Copyright © 2018年 Zhang Jonathan. All rights reserved.
//

#import "PLDiscoverableDev.h"

@implementation PLDiscoverableDev

-(NSString *)description{
    return [NSString stringWithFormat:@"uuid:%@, btAddr:%@, isCheck: %d", _uuid, _btAddr,_isCheck];
}

//重写init方法
-(id) init
{
    //调用父类的init方法执行初始化，将初始化得到的对象赋值给self对象
    //如果self不为nil,表明父类的init方法初始化成功
    if (self = [super init]) {
        self.uuid = @"";
        self.btAddr = @"";
        self.isCheck = false;
    }
    return self;
}

-(instancetype)initWithInfo:(TPScan *)device{
    //调用父类的init方法执行初始化，将初始化得到的对象赋值给self对象
    //如果self不为nil,表明父类的init方法初始化成功
    if (self = [super init]) {
        //对该对象的属性复制
        self.uuid = device.uuid;
        self.btAddr = device.btAddr;
        self.isCheck = false;
    }
    return self;
}

+(instancetype)initWithInfo:(TPScan *)device{
    return [[PLDiscoverableDev alloc]initWithInfo:device];
}

@end
