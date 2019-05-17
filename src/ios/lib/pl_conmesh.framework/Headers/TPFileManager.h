//
//  TpadFileManager.h
//  NOVA
//
//  Created by yqf on 16/3/28.
//  Copyright © 2016年 jerryDing. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface TPFileManager : NSObject

+(TPFileManager *)getInstance;

-(void)put:(NSString *)key sVal:(NSString *)value;
-(void)put:(NSString *)key iVal:(int)value;

-(NSString *)get:(NSString *) key;
-(int)get:(NSString *)key iVal:(int)defValue;

-(NSString *)get_cur_time;
-(void)remove_key:(NSString *)key;
-(void)show_allKey_val;
-(void)show_files;
-(void)show_file_by_path:(NSString *)path;
-(void)delete_all_files;
-(BOOL)copy_file_to_path:(NSString *)from to:(NSString *)to;
-(BOOL)delete_file:(NSString *)path;

@end
