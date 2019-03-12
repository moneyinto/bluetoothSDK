//
//  MeshElementInfo.h
//
//  Created by Zhang Jonathan on 2018/12/7.
//

#import <Foundation/Foundation.h>

/**
 * element_addr : 2
 * models : ["00001001","00001001","00001001"]
 * name :
 */

@interface MeshElementInfo : NSObject

@property (nonatomic, assign) short element_addr;
@property (nonatomic, copy)  NSString *name;
@property (nonatomic, strong) NSMutableArray *models;

@end

