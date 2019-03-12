//
//  MeshNetInfo.h
//
//  Created by Zhang Jonathan on 2018/12/7.
//

#import <Foundation/Foundation.h>


/**
 * netkey : 31313131000000000000000000000000
 * appkey : 31313131000000000000000000000000
 * iv_index : 0
 * node_next_addr : 10
 * admin_next_addr : 32766
 * mesh_version : 0
 * gateway : false
 * seq : 890
 * name : 11111111
 * current_admin : 20181026181557
 * admin_nodes : [{"name":"user","uuid":"20181026181557","addr":32767}]
 * nodes : [{"name":"node_0","uuid":"F0:AC:D7:00:00:F1","devkey":"6d51ea2ccd81a31efc21797703e75586","feature":3,"primary_addr":2,"configed":true,"version":"1465_1_8","element_list":[{"element_addr":2,"models":["00001001","00001001","00001001"],"name":""}]}]
 */

@interface MeshNetInfo : NSObject

@property (nonatomic, copy) NSString *netkey;
@property (nonatomic, copy) NSString *appkey;
@property (nonatomic, assign) int   iv_index;
@property (nonatomic, assign) short node_next_addr;
@property (nonatomic, assign) short admin_next_addr;
@property (nonatomic, assign) int   mesh_version;
@property (nonatomic, assign) BOOL   gateway;
@property (nonatomic, assign) int   seq;
@property (nonatomic, copy) NSString *name;
@property (nonatomic, copy) NSString *current_admin;
@property (nonatomic, strong) NSMutableArray *admin_nodes;
@property (nonatomic, strong) NSMutableArray *nodes;

+(instancetype)initWithInfo:(NSString *)netKey appKey:(NSString *) appKey;

@end

