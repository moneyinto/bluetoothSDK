//
//  PLAdvProvision.h
//  sigmesh
//
//  Created by Zhang Jonathan on 2019/1/11.
//  Copyright © 2019年 Zhang Jonathan. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface PLAdvProvision : NSObject

@property (nonatomic, copy) NSString *btAddr;
@property (nonatomic, assign) Byte ele_num;
@property (nonatomic, assign) short first_ele_addr;
@property (nonatomic, assign) short pid;
@property (nonatomic, assign) short vid;
@property (nonatomic, copy) NSString *key;
@property (nonatomic, assign) Boolean adv_start_ok;


@end

