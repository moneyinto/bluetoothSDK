//
//  TpadFileManager.h
//  NOVA
//
//  Created by yqf on 16/3/28.
//  Copyright © 2016年 jerryDing. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface PLFileManager : NSObject

+(PLFileManager *)getInstance;

-(void)put:(NSString *)key sVal:(NSString *)value;
-(void)put:(NSString *)key iVal:(int)value;

-(NSString *)get:(NSString *) key;
-(int)get:(NSString *)key iVal:(int)defValue;
-(void)save_netInfo:(NSString *)name netInfo:(NSMutableDictionary *)dict;
-(NSMutableDictionary *)get_netInfo:(NSString *)name;
-(void)del_netInfo:(NSString *)name;

-(NSString *)get_cur_time;
-(void)remove_key:(NSString *)key;
-(void)show_allKey_val;
-(void)show_files;

@end