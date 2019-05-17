//
//  test.h
//  pl_encry_mesh
//
//  Created by Zhang Jonathan on 2019/4/28.
//  Copyright © 2019年 Zhang Jonathan. All rights reserved.
//

#ifdef __OBJC__
#import <Foundation/Foundation.h>

#define PL_ENCRY_DATA	@"pl_encry_data"
#define ITEM_DEVICE		@"item_device"
#define ITEM_DATA		@"item_data"
#define ITEM_LEN		@"item_len"

//err code
#define ERR_NONE            0
#define ERR_INVALID_INPUT   1
#define ERR_UNKNOWN_TYPE    2
#define ERR_UNKNOWN_OP      3
#define ERR_DECRYPT_HOMEID  4

// Mesh Data Type
#define MESH_DATA_TYPE_CMD                1
#define MESH_DATA_TYPE_RESPONSE           2
#define MESH_DATA_TYPE_DATA_EVENT         3
#define MESH_DATA_TYPE_MESH_EVENT         4

#define MESH_DATA_TYPE_ENCRY_DATA_EVENT   6

// Mesh Cmd type
#define MESH_CMD_OP_LOGIN_WITH_PWD  0x16
#define MESH_CMD_OP_ENCRY_GETPWD  0x19
#define MESH_CMD_OP_ENCRY_GETPWD_CENTRAL  0x20

#define MESH_JOIN_TYPE_CENTRAL       0
#define MESH_JOIN_TYPE_PERIPHERAL    1

#define DEVICE_INFO_NOT_FOUND  0xff
#define DEVICE_INFO_MAX        16

void setHomeidPassword(uint8_t* homeid, uint8_t* password);
int processData(uint8_t* device, uint8_t* data, int len);
int sendEncry(uint8_t *data, int len, uint8_t *encry_data);
void meshExit(void);
void deviceDisconnected(uint8_t *device);
void genCreateData(uint8_t *in_data, uint8_t *out_data);

@interface encry_mesh : NSObject

+(encry_mesh *)getInstance;
-(void)sendData:(uint8_t*) p_device p_data:(const uint8_t*) p_data length:(uint16_t) length;

@end

#endif

