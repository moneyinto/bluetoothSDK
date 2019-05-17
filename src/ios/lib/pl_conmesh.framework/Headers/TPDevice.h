//
//  TPScene.h
//  office
//
//  Created by yqf on 16/9/21.
//  Copyright © 2016年 Jonathan. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FMDTObject.h"

//保存节点信息
@interface TPDevice : FMDTObject

@property (nonatomic, copy) NSString *homeId; //设备所属的mesh homeId

@property (nonatomic, assign) int groupId;      //设备所属的组Id
@property (nonatomic, copy) NSString *groupName;//设备所属的组名称

//设备所属的mesh当前网络节点数
//现在改为scene item所在组中的节点数
@property (nonatomic, assign) int nodes;
@property (nonatomic, assign) int idx;    //设备在当前网络中按照btAddr排序后的索引
//关键字index被数据库表格默认用掉了,因此使用index简写

@property (nonatomic, assign) int vAddr;        //蓝牙虚拟地址
@property (nonatomic, copy) NSString *btAddr;   //蓝牙地址btAddr
@property (nonatomic, copy) NSString *deviceName;//设备自定义名称
@property (nonatomic, assign) int companyId;        //设备所属的公司Id
@property (nonatomic, assign) int productId;        //设备所属的产品Id
@property (nonatomic, assign) int productIndex;     //设备所属的产品索引Index
@property (nonatomic, copy) NSString *productName;  //设备所属的产品名称
@property (nonatomic, assign) int singleCtl;        //是否为单控设备
@property (nonatomic, assign) int rtt;				// ping命令的响应时间
@property (nonatomic, copy) NSString *version;		// 设备的固件版本
@property (nonatomic, assign) int appId; 	// 4369, 4369 1.11
@property (nonatomic, assign) int verMajor; // 1
@property (nonatomic, assign) int verMinor; // 11
@property (nonatomic, assign) int unitNum;

@end
