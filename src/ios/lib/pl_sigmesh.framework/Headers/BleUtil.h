//
//  BleUtil.h
//  bleCentral
//
//  Created by yqf on 17/4/10.
//  Copyright © 2017年 Jonathan. All rights reserved.
//

#import <Foundation/Foundation.h>

short byte2short(Byte *input, int offset);
int byte2int(Byte *input, int offset);
void short2byte(short input, Byte *output, int offset);
void int2byte(int input, Byte *output, int offset);
void long2byte_time(long input, Byte *output, int offset);
BOOL byte_equal(Byte *a, Byte *b, int offset, int length);

@interface BleUtil : NSObject

+(NSData*)hexStringToData:(NSString*)str;
+(NSString*)combineBtAddr:(Byte *)data startPos:(int)pos len:(unsigned long)len;
+(NSString *)data2HexStr:(NSData *)data;
+(NSString *)byte2HexStr:(Byte *)data len:(NSInteger)len;
+(void)hexStr2Byte:(NSString *)info data:(Byte *)data;
+(void)hexStr2Byte:(NSString *)info data:(Byte *)data len:(int)len;
+(NSString *)getBtAddr:(NSString *)name;
+(void)getBtAddr:(NSString *)btAddr data:(Byte *)data;
+(NSTimeInterval)cur_time_stamp;//unit: sec
+(UInt64)cur_time_stamp_ms;     //unit: ms

@end
