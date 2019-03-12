//
//  PLSigMeshModelMsg.h
//  sigmesh
//
//  Created by Zhang Jonathan on 2018/12/7.
//  Copyright © 2018年 Zhang Jonathan. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "types.h"

@interface PLSigMeshModelMsg : NSObject

+(PLSigMeshModelMsg *)getInstance;

-(void)NodeReset:(short)dst dev_key:(uint8_t *)dev_key;
-(void)SubsAddDel:(short) op dst:(short)dst ele_addr:(short)ele_addr company:(short)company model:(short)model subs_addr:(short)subs_addr dev_key:(uint8_t *)dev_key;

-(void)OnOffSendGet:(short) dst appKeyIdx:(int) appKeyIdx;
-(void)OnOffSendSet:(short)dst targetState:(uint8_t)targetState transmitTime:(uint8_t)transmitTime delay:(uint8_t)delay appKeyIdx:(int)appKeyIdx ack:(BOOL)ack;
-(void)LevelSendGet:(short)dst appKeyIdx:(int)appKeyIdx;
-(void)LevelSendSet:(short)dst level:(short)level transitionTime:(uint8_t)transitionTime delay:(uint8_t)delay appKeyIdx:(int)appKeyIdx ack:(BOOL)ack;
-(void)LevelSendSetDelta:(short)dst delta:(int)delta transitionTime:(uint8_t)transitionTime delay:(uint8_t)delay appKeyIdx:(int)appKeyIdx ack:(BOOL)ack;
-(void)LevelSendMove:(short)dst level:(short)level transitionTime:(uint8_t)transitionTime delay:(uint8_t)delay appKeyIdx:(int)appKeyIdx;
-(void)PowerLevelSendSet:(short)dst level:(short)level transitionTime:(uint8_t)transitionTime delay:(uint8_t)delay appKeyIdx:(int)appKeyIdx ack:(BOOL)ack;
-(void)PowerLevelSendGet:(short)dst appKeyIdx:(int)appKeyIdx;

-(void)SceneSendStore:(short)dst scene_number:(short)scene_number appKeyIdx:(int)appKeyIdx;
-(void)SceneSendRegGet:(short)dst appKeyIdx:(int)appKeyIdx;
-(void)SceneSendDelete:(short)dst scene_number:(short)scene_number appKeyIdx:(int)appKeyIdx;
-(void)SceneSendRecall:(short)dst scene_number:(short)scene_number transitionTime:(uint8_t)transitionTime delay:(uint8_t)delay appKeyIdx:(int)appKeyIdx ack:(BOOL)ack;

-(void)VendorCommonGetVer:(short)dst appKeyIdx:(int)appKeyIdx;
-(void)VendorDemoEnableCounter:(short)dst enable:(uint8_t)enable appKeyIdx:(int)appKeyIdx;
-(void)VendorDemoGetCounter:(short)dst appKeyIdx:(int)appKeyIdx;
-(void)VendorOnoffToggle:(short)dst appKeyIdx:(int)appKeyIdx;
-(void)VendorLevelToggle:(short)dst delta:(int)delta appKeyIdx:(int)appKeyIdx;
-(void)VendorSwitchFuncSet:(short)dst target_addr:(short)target_addr index:(uint8_t)index func:(uint8_t)func para:(int)para appKeyIdx:(int)appKeyIdx;
-(void)VendorLevelStop:(short)dst appKeyIdx:(int)appKeyIdx;
-(void)VendorCurtainChangeDir:(short)dst appKeyIdx:(int)appKeyIdx;
-(void)VendorDeltaLevel:(short)dst delta:(short)delta appKeyIdx:(int)appKeyIdx;
-(void)VendorUartSend:(short)dst uart_data:(uint8_t *)uart_data len:(int) data_len appKeyIdx:(int)appKeyIdx;

-(void)VendorJiechangConfigSet:(short)dst enable:(uint8_t)enable total_addr:(short)total_addr node_interval:(int)node_interval round_interval:(int)round_interval appKeyIdx:(int)appKeyIdx;
-(void)VendorJiechangConfigGet:(short)dst appKeyIdx:(int)appKeyIdx;

@end

