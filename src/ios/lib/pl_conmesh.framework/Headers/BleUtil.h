//
//  BleUtil.h
//  smartcar
//
//  Created by yqf on 16/6/7.
//  Copyright © 2016年 Jonathan. All rights reserved.
//

#import <Foundation/Foundation.h>

#define PL_OK  					0
#define PL_BT_ERR  				1
#define PL_BT_ALREADY_CONNECTED 2
#define PL_INTERNAL_ERR  		3
#define PL_INPUT_ERR			4
	
short byte2short(Byte *input, int offset);
int byte2int(Byte *input, int offset);
void short2byte(short input, Byte *output, int offset);
void int2byte(int input, Byte *output, int offset);
int byte2intBig(Byte *input, int offset);
void long2byte_time(long input, Byte *output, int offset);
BOOL byte_equal(Byte *a, Byte *b, int offset, int length);

@interface BleUtil : NSObject

+(NSData*)hexStringToData:(NSString*)str;
+(void)int2byteArray:(int)res data:(Byte *)data;
+(float)combineByte_float:(Byte *)bArray startPos:(int)startPos;
+(int)combineByte_int:(Byte *)bArray startPos:(int)startPos len:(int)len;
+(BOOL)isPureInt:(NSString *)string;
+ (NSData *)int2data:(NSInteger)value reverse:(BOOL)reverse;
+(NSString*)combineBtAddr:(Byte *)data startPos:(int)pos len:(unsigned long)len;
+(int)data2int:(NSData *)data;
+(NSData*)int2data:(int)data;
+(short)combineByte_short:(Byte *)bArray startPos:(int)startPos;
+(NSString*)combineBtAddr:(Byte *)data startPos:(int)pos;
+(NSString *)int2NSString:(int)value isBig:(BOOL)isBig;
+(NSString *)byte2HexStr:(Byte *)bArray len:(int)len;
+(void)getBtAddr:(NSString *)str btAddr:(Byte *)btAddr;
+(NSTimeInterval)cur_time_stamp;
+(UInt64)cur_time_stamp_ms;

@end
