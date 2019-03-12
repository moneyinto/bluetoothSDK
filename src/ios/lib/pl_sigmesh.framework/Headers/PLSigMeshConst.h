//
//  PLSigMeshConst.h
//  sigmesh
//
//  Created by Zhang Jonathan on 2018/12/7.
//  Copyright © 2018年 Zhang Jonathan. All rights reserved.
//

#ifndef PLSigMeshConst_h
#define PLSigMeshConst_h

#define FILE_PL_SIG_MESH            @"pl_sig_mesh.plist"
#define PL_SIG_MESH_PHONE_UUID      @"pl_sig_mesh_phone_uuid"
#define MESH_INFO_NAME              @"meshInfo_%@.plist"
#define MESH_NET_NUM                @"net_num"

#define CUR_DEVICE_UUID             @"curDeviceUUID"
#define NOTIFY_REFRESH_NET_LIST     @"notifyRefreshNetList"
#define NOTIFY_ADDING_NODE          @"notifyAddingNode"
#define NOTIFY_REFRESH_UI           @"notifyRefreshUI"
#define NOTIFY_PL_ADV_DEVICE        @"notifyPlAdvDevice"
#define ITEM_ADV_TIME               @"itemAdvTime"
#define PL_SIG_PROVISION_UUID       @"1827"
#define PL_SIG_CONFIG_UUID          @"1828"
#define PL_SIG_JOIN_UUID            @"1828"

#define PL_OK 			0
#define PL_BT_ERR 		1
#define PL_INPUT_PARA 	2
#define PL_MTU_ERR 		3
#define PL_SERVICE_ERR 	4
#define PL_SEND_LOST_CONNECTION 	5
#define PL_SEND_NO_SERVICE 			6
#define PL_MESH_NET_NULL 			7 
#define PL_MESH_NET_JOIN_STATE_ERR 	8 

#define SCAN_TYPE_PROXY 	0
#define SCAN_TYPE_PROVISION 1

#define MTU_SIZE_GATT 		256

#define PROVISOIN_FLAG_NONE 0//spec 5.4.2.5

    //event from lib to app layer
#define PL_EVT_PROVISON_SUCCESS 	0x0000
#define PL_EVT_PROVISON_FAIL 		0x0001

#define PL_EVT_CONFIG_SUCCESS 		0
#define PL_EVT_CONFIG_ERR_CID_PID 	1
#define PL_EVT_CONFIG_ERR_MODELID_MISMATCH 	2
#define PL_EVT_CONFIG_ERR_CONNECTION 		3
//#define PL_EVT_CONFIG_FAIL 0x0003
#define PL_EVT_PROVISON_SCAN_FAIL 			0x0004
//event from lib to app layer end

    //event from PlSigMeshProvisionClient to PlSigMeshService
#define PL_EVT_PROVISON_TO_SERVICE_PROVISION_OK 0x0000
#define PL_EVT_PROXY_TO_SERVICE_CONFIG_OK 		0x0001
#define PL_EVT_PROXY_TO_SERVICE_CONFIG_FAIL 	0x0002
#define PL_EVT_PROXY_TO_SERVICE_READY 			0x0003
//event from lib to app layer end

    //event from jni
#define MESH_EVT_PROVISON_CAPABITIES 	0x0000
#define MESH_EVT_PROVISON_DEV_KEY 		0x0001
#define MESH_EVT_PROVISON_COMPLETE 		0x0002
#define MESH_EVT_PROVISON_FAIL 			0x0003
#define MESH_EVT_CONFIG_OK 				0x0004
#define MESH_EVT_CONFIG_FAIL 			0x0005
#define MESH_EVT_PROXY_ACCESS_PAYLOAD 	0x0006
#define MESH_EVT_COMPOS_DATA_GET 		0x0007

#define MESH_COMPANY_ID_BT_SIG 			0x0000

#define PL_MESH_EXIT 		0x0000
#define PL_MESH_JOIN_START 	0x0001
#define PL_MESH_JOINING 	0x0002
#define PL_MESH_JOINED      0x0003

#define PL_PROXY_CONNECT_RETRY_MAX_TIME 	5
#define PL_CONFIG_CONNECT_RETRY_MAX_TIME 	5

#define PL_DEFAULT_APP_KEY_INDEX 	0
#define PL_DEFAULT_DEV_KEY_INDEX 	255
#define PL_NODE_NOT_FOUND 			0xffffffff
#define PL_GROUP_BASE 				0xc000
#define PL_ADDR_ALL 				(short) 0xffff
#define PL_SEQ_UPDATE 				10

#define PL_SIG_MODEL_ONOFF 			0x1000
#define PL_SIG_MODEL_ONOFF_CLIENT 	0x1001

#define PL_SIG_MODEL_LEVEL_SERVER 		0x1002
#define PL_SIG_MODEL_POWER_LEVEL_SRV 	0x1009
#define PL_SIG_MODEL_POWER_LEVEL_SETUP_SRV 0x100a
    //sig opcode
    //onoff
#define PL_OP_SIG_GENERIC_ONOFF_GET (short) 0x8201
#define PL_OP_SIG_GENERIC_ONOFF_SET (short) 0x8202
#define PL_OP_SIG_GENERIC_ONOFF_SET_UNACKED (short) 0x8203
#define PL_OP_SIG_GENERIC_ONOFF_STATUS (short) 0x8204

    //level
#define PL_OP_SIG_GENERIC_LEVEL_GET 		(short) 0x8205
#define PL_OP_SIG_GENERIC_LEVEL_SET 		(short) 0x8206
#define PL_OP_SIG_GENERIC_LEVEL_SET_UNACKED (short) 0x8207
#define PL_OP_SIG_GENERIC_LEVEL_STATUS 		(short) 0x8208
#define PL_OP_SIG_GENERIC_LEVEL_DELTASET 	(short) 0x8209
#define PL_OP_SIG_GENERIC_LEVEL_DELTASET_UNACKED (short) 0x820a
#define PL_OP_SIG_GENERIC_LEVEL_MOVE 		(short) 0x820b
#define PL_OP_SIG_GENERIC_LEVEL_MOVE_UNACK 	(short) 0x820c

    //power level
#define PL_OP_SIG_GENERIC_PWRLEVEL_GET          (short) 0x8215
#define PL_OP_SIG_GENERIC_PWRLEVEL_SET 			(short) 0x8216
#define PL_OP_SIG_GENERIC_PWRLEVEL_SET_UNACK 	(short) 0x8217
#define PL_OP_SIG_GENERIC_PWRLEVEL_STATUS 		(short) 0x8218
#define PL_OP_SIG_GENERIC_PWRLEVEL_GET_LAST 	(short) 0x8219
#define PL_OP_SIG_GENERIC_PWRLEVEL_GET_DEFAULT 	(short) 0x821b

    //time
#define PL_OP_SIG_TIME_GET (short) 		0x8237
#define PL_OP_SIG_TIME_SET (short) 		0x5c
#define PL_OP_SIG_TIME_STATUS (short) 	0x5d

    //scene
#define PL_OP_SIG_SCENE_GET 		(short) 0x8241
#define PL_OP_SIG_SCENE_RECALL 		(short) 0x8242
#define PL_OP_SIG_SCENE_RECALL_UNACK (short) 0x8243
#define PL_OP_SIG_SCENE_STATUS 		(short) 0x5e
#define PL_OP_SIG_SCENE_REG_GET 	(short) 0x8244
#define PL_OP_SIG_SCENE_REG_STATUS 	(short) 0x8245
#define PL_OP_SIG_SCENE_STORE 		(short) 0x8246
#define PL_OP_SIG_SCENE_STORE_UNACK (short) 0x8247
#define PL_OP_SIG_SCENE_DEL 		(short) 0x829e
#define PL_OP_SIG_SCENE_DEL_UNACK 	(short) 0x829f

    //subs
#define PL_OP_SIG_SUBS_ADD 		(short) 0x801b
#define PL_OP_SIG_SUBS_DEL 		(short) 0x801c
#define PL_OP_SIG_SUBS_DELALL 	(short) 0x801d
#define PL_OP_SIG_SUBS_OVERWRITE (short) 0x801e
#define PL_OP_SIG_SUBS_STATUS 	(short) 0x801f
#define PL_OP_SIG_SIG_SUBS_GET 	(short) 0x8029
#define PL_OP_SIG_SIG_SUBS_LIST (short) 0x802a
#define PL_OP_SIG_VENDOR_SUBS_GET (short) 0x802b
#define PL_OP_SIG_VENDOR_SUBS_LIST (short) 0x802c

#define PL_OP_SIG_NODE_RESET 		(short) 0x8049
#define PL_OP_SIG_NODE_RESET_STATUS (short) 0x804a

    //publication
#define PL_OP_SIG_PUB_SET 	(short) 0x03
#define PL_OP_SIG_PUB_GET 	(short) 0x8018
#define PL_OP_SIG_PUB_STATUS (short) 0x8019

    //relay set
#define PL_OP_SIG_PROXY_SET (short) 0x8013

    //relay set
#define PL_OP_SIG_RELAY_SET (short) 0x8027
//sig opcode end


    //sig onoff model define
#define PL_SIG_ONOFF_SET_OFF 	0
#define PL_SIG_ONOFF_SET_ON 	1

#define PL_DEFAULT_ONOFF_TRANSITIONTIME 0
#define PL_DEFAULT_ONOFF_DELAY 	0
//sig onoff model define end

    //vendor msg
#define PL_COMPANY_ID 0x05b9
    //op for vendor model common
#define PL_OP_VENDOR_COMMON_CONFIG_OK 	0x01
#define PL_OP_VENDOR_COMMON_GET_VER 	0x02
#define PL_OP_VENDOR_COMMON_VER_STATUS 	0x03
#define PL_OP_VENDOR_COMMON_TOGGLE_ONOFF 0x04
#define PL_OP_VENDOR_COMMON_TOGGLE_LEVEL 0x05
    //op for vendor model demo
#define PL_OP_VENDOR_DEMO_ENABLE_COUNTER 	(short)0x3f
#define PL_OP_VENDOR_DEMO_GET_COUNTER 		(short)0x3e
#define PL_OP_VENDOR_DEMO_COUNTER_STATUS 	(short)0x3d

    //op for vendor model insona
#define PL_OP_VENDOR_FUNC_SET 		0x06
#define PL_OP_VENDOR_FUNC_GET 		0x07
#define PL_OP_VENDOR_FUNC_STATUS 	0x08
#define PL_OP_VENDOR_CURTAIN_STOP 	0x09
#define PL_OP_VENDOR_CURTAIN_CHANGE_DIR 0x0a
#define PL_OP_VENDOR_DELTA_LEVEL    0x0b

//op for uart common
#define PL_OP_VENDOR_UART_DATA 0x01

//02,03 version
#define PL_OP_VENDOR_JIECHANG_CONFIG_GET    0x3f
#define PL_OP_VENDOR_JIECHANG_CONFIG_SET    0x3e
#define PL_OP_VENDOR_JIECHANG_CONFIG_STATUS 0x3d
//end


#define BTN_FUNC_DEFAULT 	0x00
#define BTN_FUNC_ON 		0x01
#define BTN_FUNC_OFF 		0x02
#define BTN_FUNC_ONOFF_TOGGLE 	0x03
#define BTN_FUNC_LEVEL_DELTA 	0x04
#define BTN_FUNC_LEVEL_TOGGLE 	0x05
#define BTN_FUNC_SCENE 		0x06
#define BTN_FUNC_MAX 		0x07

#define CONFIG_MODE_PROVISION_ONE_BY_ONE 		0
#define CONFIG_MODE_PROVISION_CONFIG_ONE_BY_ONE 1

#define SEND_DEFAULT_DELAY 10
#define SEND_CONFIG_DELAY 150


#endif /* PLSigMeshConst_h */
