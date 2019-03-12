//
//  MeshNodeInfo.h
//
//  Created by Zhang Jonathan on 2018/12/7.
//

#import <Foundation/Foundation.h>

/**
 * name : node_0
 * uuid : F0:AC:D7:00:00:F1
 * devkey : 6d51ea2ccd81a31efc21797703e75586
 * feature : 3
 * primary_addr : 2
 * configed : true
 * version : 1465_1_8
 * element_list : [{"element_addr":2,"models":["00001001","00001001","00001001"],"name":""}]
 */

@interface MeshNodeInfo : NSObject

@property (nonatomic, copy) NSString *name;
@property (nonatomic, copy) NSString *uuid;
@property (nonatomic, copy) NSString *devkey;
@property (nonatomic, assign) short feature;
@property (nonatomic, assign) short primary_addr;
@property (nonatomic, assign) BOOL  configed;
@property (nonatomic, copy) NSString *version;
@property (nonatomic, strong) NSMutableArray *element_list;

@end

