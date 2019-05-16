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

@property (nonatomic, assign) int addr;
@property (nonatomic, copy) NSString *name;
@property (nonatomic, assign) short node_next_addr;
@property (nonatomic, assign) int provision_end_addr; // <502
@property (nonatomic, assign) int provision_start_addr; // >=2
@property (nonatomic, copy) NSString *uuid;

@end

