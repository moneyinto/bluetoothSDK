//
//  AdminNodeInfo.h
//
//  Created by Zhang Jonathan on 2018/12/7.
//

#import <Foundation/Foundation.h>

/**
 * name : user
 * uuid : 20181026181557
 * addr : 32767
 */

@interface AdminNodeInfo : NSObject

@property (nonatomic, copy) NSString *name;
@property (nonatomic, copy) NSString *uuid;
@property (nonatomic, assign) int addr;

@end

