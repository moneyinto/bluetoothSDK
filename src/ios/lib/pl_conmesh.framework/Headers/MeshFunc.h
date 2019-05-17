//
//  MeshFunc.h
//  conMesh
//
//  Created by Zhang Jonathan on 2019/4/30.
//  Copyright © 2019年 Zhang Jonathan. All rights reserved.
//

#import <Foundation/Foundation.h>

#define ACK_TYPE_NONE     		0
#define ACK_TYPE_REMOTE   		1
#define ACK_TYPE_ALL      		2

#define UNIT0   0
#define UNIT1   1
#define UNIT2   2
#define UNIT3   3
#define UNIT4 	4
#define UNIT5 	5
#define UNIT6 	6
#define UNIT7 	7
#define UNIT8 	8
#define UNIT9 	9
#define UNIT10 10
#define UNIT11 11
#define UNIT12 12
#define UNIT13 13
#define UNIT14 14
#define UNIT15 15

@interface MeshFunc : NSObject
+(MeshFunc *)getInstance;

-(short)unitListToMask:(NSArray *)unitList;
-(void)onoffSet:(Byte*)targetVaddr unitMask:(short)unitMask onoff:(Byte)onoff ackType:(Byte)ackType isMac:(BOOL)isMac;
-(void)onoffSetGroup:(Byte)groupId onoff:(Byte)onoff ackType:(Byte)ackType;

-(void)levelSet:(Byte *)targetVaddr unitMask:(short)unitMask level:(short)level ackType:(Byte) ackType;
-(void)levelSetGroup:(Byte)groupId level:(short)level ackType:(Byte) ackType;

-(void)exitDevice:(Byte *)targetVaddr;
-(void)deleteDevice:(Byte *)targetVaddr;
-(void)rebootDevice:(Byte *)targetVaddr;

-(void)vendorSend:(Byte *) targetVaddr unitMask:(short) unitMask vendorOp:(short) vendorOp inData:(Byte *) inData len:(int)len;
-(void)vendorSendGroup:(Byte) groupId vendorOp:(short) vendorOp data:(Byte *) data len:(short) len;

-(void)sceneAddDel:(Byte *) targetVaddr unitMask:(short) unitMask sceneId:(Byte) sceneId addDel:(BOOL) addDel ackType:(Byte) ackType;
-(void)sceneAddDelGroup:(Byte) groupId sceneId:(Byte) sceneId addDel:(BOOL) addDel ackType:(Byte) ackType;
-(void) sceneRegGet:(Byte *) targetVaddr unitMask:(short) unitMask;
-(void) sceneRegGetGroup:(Byte) groupId;
-(void) sceneRecall:(Byte *) targetVaddr unitMask:(short) unitMask sceneId:(Byte) sceneId ackType:(Byte) ackType;
-(void) sceneRecallGroup:(Byte) groupId sceneId:(Byte) sceneId ackType:(Byte) ackType;

-(void) groupAddDel:(Byte *) targetVaddr unitMask:(short) unitMask groupId:(Byte) groupId addDel:(BOOL) addDel ackType:(Byte) ackType;

-(void) GenGroupControlPacket:(Byte) groupId srcUnitIndex:(Byte) srcUnitIndex addrType:(Byte) addrType addr:(Byte *) addr opcode:(short) opcode data:(Byte *) data len:(short) len ;
-(short) GenUnitControlPacket:(short) targetUnitMask srcUnitIndex:(Byte) srcUnitIndex addrType:(Byte) addrType addr:(Byte *) addr opcode:(short) opcode data:(Byte *) data len:(short) len;
//-(void) FuncMsgHandler:(PacketSource *) src dataOffset:(short) dataOffset data:(Byte *) data len:(Byte) len;
-(void) FuncDataHandler:(Byte * )data len:(Byte) len;
-(void) ping:(Byte*)targetVaddr isMac:(BOOL)isMac;
-(void) nameSet:(Byte *) targetVaddr data:(Byte *) data len:(short) len ackType:(Byte) ackType isMac:(BOOL) isMac;
-(void) nameSetGroup:(Byte) groupId data:(Byte *) data len:(short) len ackType:(Byte) ackType;
-(void) nameGet:(Byte *) targetVaddr isMac:(BOOL) isMac;

-(NSMutableArray *)getUnitInfoList:(NSString *)btAddr;

@end

