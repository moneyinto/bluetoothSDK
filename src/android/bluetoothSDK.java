package com.jieweifu.bluetoothSDK;

import android.bluetooth.BluetoothDevice;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Build;
import android.os.IBinder;
import android.util.Log;

import com.pairlink.connectedmesh.lib.MeshCallback;
import com.pairlink.connectedmesh.lib.MeshFunc;
import com.pairlink.connectedmesh.lib.MeshService;
import com.pairlink.connectedmesh.lib.util.BleUtil;
import com.pairlink.connectedmesh.lib.util.DeviceBean;
import com.pairlink.connectedmesh.lib.util.PlLog;
import com.pairlink.connectedmesh.lib.util.Util;

import org.apache.cordova.CordovaArgs;
import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.CallbackContext;

import org.apache.cordova.PluginResult;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.lang.reflect.Method;

import static android.Manifest.permission.*;

/**
 * This class echoes a string called from JavaScript.
 */
public class BluetoothSDK extends CordovaPlugin {

    @Override
    protected void pluginInitialize() {
        super.pluginInitialize();
        cordova.getActivity().startService(new Intent(cordova.getActivity(), MeshService.class));
    }

    private static BluetoothSDK instance;

    private CallbackContext meshListenerCallback;

    private CallbackContext listenerWifiJoinStatusCallback;

    private CallbackContext scanDeviceCallback;

    private CallbackContext addDeviceCallback;

    private CallbackContext deleteDeviceCallback;

    public BluetoothSDK() {
        instance = this;
    }

    private class MeshDev {
        private String btaddr;
        private short addr;
        private int ele_index;
        private short feature;
        private boolean is_config;
        private List<String> group_list = new ArrayList<String>();
        private String version;
        private boolean onoff;// false off, true on
        private short level = 0;

        private boolean counter_enable = false;
        private int counter;
        private long msg_transmit_time = 0;
    }

    @Override
    public boolean execute(final String action, final CordovaArgs args, final CallbackContext callbackContext)
            throws JSONException {
        cordova.getThreadPool().execute(new Runnable() {
            @Override
            public void run() {
                try {
                    Method method = BluetoothSDK.class.getDeclaredMethod(action, CordovaArgs.class,
                            CallbackContext.class);
                    method.invoke(BluetoothSDK.this, args, callbackContext);
                } catch (Exception e) {
                    Log.e("", e.toString());
                }
            }
        });
        return true;
    }

//    private final PlSigMeshProxyCallback mSigMeshProxyCB = new PlSigMeshProxyCallback() {
//        @Override
//        public void onNodeResetStatus(final short src) {
//            // 删除解绑回调 强制删除配置文件
//            mService.delMeshNode(src);
//            unbindDeviceCallback.success(src);
//        }
//
//        @Override
//        public void onConfigComplete(int result, MeshNetInfo.MeshNodeInfo config_node, MeshNetInfo mesh) {
//            if (result != Util.PL_EVT_CONFIG_SUCCESS) {
//                String tmp = "";
//                if (result == Util.PL_EVT_CONFIG_ERR_CID_PID) {
//                    tmp = "ERR CID PID";
//                } else if (result == Util.PL_EVT_CONFIG_ERR_MODELID_MISMATCH) {
//                    tmp = "ERR MODEL";
//                } else if (result == Util.PL_EVT_CONFIG_ERR_MODELID_MISMATCH) {
//                    tmp = "ERR Connection";
//                }
//                Log.d("DDD_CONFIG_ERR", "------------------");
//                return;
//            }
//
//            final String addr = config_node.uuid;
//
//            if (Util.CONFIG_MODE_PROVISION_CONFIG_ONE_BY_ONE == mService.get_config_mode()) {
//                Log.d("DDD_1", "---------------");
//                // 配置完成
//            }
//
//            if (Util.CONFIG_MODE_PROVISION_ONE_BY_ONE == mService.get_config_mode()) {
//                Log.d("DDD_2", "---------------");
//            }
//
//            try {
//                JSONObject response = new JSONObject();
//                response.put("progress", 100);
//                bindDeviceProgressCallback.success(response);
//            } catch (Exception e) {
//                Log.e("", e.toString());
//            }
//        }
//
//        @Override
//        public void onVendorUartData(short src, byte[] data) {
//            Log.d("", "onVendorUartData " + src + " " + Util.byte2HexStr(data));
//        }
//
//        @Override
//        public void onMeshStatus(int status, String addr) {
//            // 如何确认是否加入成功
//            Log.w("EEE", "onMeshStatus " + status + "---" + addr);
//            try {
//                JSONObject response = new JSONObject();
//                response.put("status", status);
//                PluginResult result = new PluginResult(PluginResult.Status.OK, response);
//                result.setKeepCallback(true);
//                meshListenerCallback.sendPluginResult(result);
//            } catch (Exception e) {
//                Log.e("", e.toString());
//            }
//            switch (status) {
//            case Util.PL_MESH_READY:
//                // mesh_status_info = "Mesh Joined " + addr;
//
//                if (mService.get_config_mode() == Util.CONFIG_MODE_PROVISION_ONE_BY_ONE) {
//                    for (int i = 0; i < MeshNet.nodes.size(); i++) {
//                        if (!MeshNet.nodes.get(i).configed) {
//                            mService.configNode(MeshNet.nodes.get(i).element_list.get(0).element_addr);
//                            return;
//                        }
//                    }
//                }
//                break;
//            case Util.PL_MESH_JOIN_FAIL:
//                // mesh_status_info = "Mesh Join Fail";
//
//                break;
//            case Util.PL_MESH_EXIT:
//                // mesh_status_info = "Mesh Exited";
//                break;
//            }
//        }
//    };
//
//    public ServiceConnection mConnection = new ServiceConnection() {
//        @Override
//        public void onServiceConnected(ComponentName name, IBinder service) {
//            Log.d("", "PlSigMeshService ServiceConnected");
//            PlSigMeshService.LocalBinder binder = (PlSigMeshService.LocalBinder) service;
//            mService = binder.getService();
//            mService.registerProxyCb(mSigMeshProxyCB);
//        }
//
//        @Override
//        public void onServiceDisconnected(ComponentName name) {
//            Log.d("", "PlSigMeshService onServiceDisconnected");
//            mService = null;
//        }
//    };
//
//    private final PlSigMeshProvisionCallback mSigMeshProvisionCB = new PlSigMeshProvisionCallback() {
//        @Override
//        public void onDeviceFoundUnprovisioned(final BluetoothDevice device, int rssi, final String uuid) {
//            Log.d("AAA", "onDeviceFoundUnprovisioned");
//            cordova.getActivity().runOnUiThread(new Runnable() {
//                @Override
//                public void run() {
//                    try {
//                        Log.d("AAA", device.getAddress() + ", " + device.getName() + ", uuid:" + uuid);
//                        addDev(device);
//                        JSONObject response = new JSONObject();
//                        response.put("address", device.getAddress());
//                        response.put("name", device.getName());
//                        response.put("uuid", uuid);
//                        PluginResult result = new PluginResult(PluginResult.Status.OK, response);
//                        result.setKeepCallback(true);
//                        registerScanDevicesCallback.sendPluginResult(result);
//                    } catch (Exception e) {
//                        Log.e("", e.toString());
//                    }
//                }
//            });
//        }
//
//        @Override
//        public void onProvisionComplete(int result, MeshNetInfo.MeshNodeInfo provision_node, MeshNetInfo mesh) {
//            Log.d("BBB", "onProvisionComplete " + result);
//            Log.d("BBB", "onProvisionComplete " + provision_node);
//            Log.d("BBB", "onProvisionComplete " + mesh);
//
//            if (Util.CONFIG_MODE_PROVISION_ONE_BY_ONE == mService.get_config_mode()) {
//
//            }
//            if (Util.CONFIG_MODE_PROVISION_CONFIG_ONE_BY_ONE == mService.get_config_mode()) {
//
//            }
//            // 配置完成50%
//            try {
//                JSONObject response = new JSONObject();
//                response.put("progress", 50);
//                PluginResult progress = new PluginResult(PluginResult.Status.OK, response);
//                progress.setKeepCallback(true);
//                bindDeviceProgressCallback.sendPluginResult(progress);
//            } catch (Exception e) {
//                Log.e("", e.toString());
//            }
//        }
//
//        @Override
//        public void onAdvProvisionComplete(MeshNetInfo mesh, List<Util.AdvProvision> advProvisionList) {
//            Log.d("CCC", "onProvisionComplete " + mesh);
//        }
//    };

    private final MeshCallback mcallback = new MeshCallback() {
        public void onDataReceived(byte type, byte[] data, boolean broadcast_flag) {
            Log.w("", "on_recv, type:" + type + " flag:" + broadcast_flag + " " + BleUtil.bytesToHexString(data));
            if(data.length == 15 && type == (byte)0xfb){//for ota
                short index = (short) ((data[14] & 0xff) << 8 | data[13] & 0xff);
                {
                    Log.w("", "net ota recv index " + index + ", change offset ");
                }
            }
        }
        public void onHomeidFound(final String id, final String name){
            try {
                JSONObject response = new JSONObject();
                response.put("wifiId", id);
                response.put("wifiName", name);
                PluginResult result = new PluginResult(PluginResult.Status.OK, response);
                result.setKeepCallback(true);
                meshListenerCallback.sendPluginResult(result);
            } catch (Exception e) {
                Log.e("", e.toString());
            }
        }
        public void onAdvertiseCallback(int errorcode) {
            PlLog.w("", "onAdvertiseCallback " + errorcode);
        }
        public void onMeshStatusChanged(final int status, final String addr) {
            // 0: MeshStatusScaning 1: MeshStatusConnecting 2: MeshStatusReconnecting 3: MeshStatusConnected 4: MeshStatusConnectionReady
            // 5: MeshStatusDisconnected 6: MeshStatusWelcome 7: MeshStatusMeshChanged 8: MeshStatusMeshListChanged 9: MeshStatusWrongPwd
            if (status == MeshService.MeshStatusMeshChanged) MeshService.getInstance().pingAll();
            Log.i("", "onMeshStatusChanged " + status);
            try {
                JSONObject response = new JSONObject();
                response.put("status", status);
                response.put("addr", addr);
                PluginResult result = new PluginResult(PluginResult.Status.OK, response);
                result.setKeepCallback(true);
                listenerWifiJoinStatusCallback.sendPluginResult(result);
            } catch (Exception e) {
                Log.e("", e.toString());
            }
        }

        public void onDiscoverableDeviceFound(final BluetoothDevice device){
            Log.w("", device.getAddress() + ", " + device.getName());
            try {
                JSONObject response = new JSONObject();
                response.put("device", device);
                PluginResult result = new PluginResult(PluginResult.Status.OK, response);
                result.setKeepCallback(true);
                scanDeviceCallback.sendPluginResult(result);
            } catch (Exception e) {
                Log.e("", e.toString());
            }
        }

        public void onDeviceAddStatus(final String addr, final int status){
            Log.w("", "onDeviceAddStatus " + addr + " " + status);
            try {
                JSONObject response = new JSONObject();
                response.put("success", Util.PL_OK == status);
                response.put("addr", addr);
                PluginResult result = new PluginResult(PluginResult.Status.OK, response);
                addDeviceCallback.sendPluginResult(result);
            } catch (Exception e) {
                Log.e("", e.toString());
            }
        }

        public void onGroupStatus(byte srcType, byte[] addr, byte status, byte groupId, short unitMask){
            Log.w("", "##onGroupStatus " + status + " " + Util.byte2HexStr(addr) + " " + groupId + " " + Integer.toHexString(unitMask & 0x0000FFFF));
        }

        public void onOnoffStatus(byte srcType, byte[] addr, byte unitIndex, byte onoff){
            Log.w("", "##onOnoffStatus " + onoff + " " + Util.byte2HexStr(addr) + " " + unitIndex);
        }

        public void onLevelStatus(byte srcType, byte[] addr, byte unitIndex, short level){
            Log.w("", "##onLevelStatus " + (0x0ffff & level) + " " + Util.byte2HexStr(addr) + " " + unitIndex);
        }

        public void onSceneRegStatus(byte srcType, byte[] addr, byte unitIndex, byte status, byte sceneId){
            Log.w("", "##onSceneRegStatus " + status + " " + Util.byte2HexStr(addr) + " " + sceneId + " " + unitIndex);
        }

        public void onSceneRecallStatus(byte srcType, byte[] addr, byte unitIndex, byte status, byte sceneId){
            Log.w("", "##onSceneRecallStatus " + status + " " + Util.byte2HexStr(addr) + " " + sceneId + " " + unitIndex);
        }

        public void onDeviceExited(byte srcType, byte[] addr){
            Log.w("", "##onDeviceExited " + Util.byte2HexStr(addr));
        }

        public void onDeviceDeleted(byte srcType, byte[] addr, byte status){
            Log.w("", "##onDeviceDeleted " + Util.byte2HexStr(addr));
            deleteDeviceCallback.success(Util.byte2HexStr(addr));
        }
    };

    private JSONArray getDeviceList() throws JSONException {
        List<DeviceBean> list = MeshService.getInstance().API_get_list();
        JSONArray devices = new JSONArray();
        for (DeviceBean device : list) {
            JSONObject deviceObj = new JSONObject();
            deviceObj.put("btAddrStr", device.btAddrStr);
            deviceObj.put("appId", device.appId);
            deviceObj.put("companyId", device.companyId);
            deviceObj.put("deviceName", device.deviceName);
            deviceObj.put("productId", device.productId);
            deviceObj.put("rtt", device.rtt);
            deviceObj.put("state", device.state);
//            deviceObj.put("unitInfoList", device.unitInfoList);
            deviceObj.put("unitNum", device.unitNum);
//            deviceObj.put("vAddr", BleUtil.bytesToHexString(device.vAddr));
            deviceObj.put("ver", device.ver);
            devices.put(deviceObj);
        }
        return devices;
    }

    private DeviceBean getDeviceIndexByBtAddr(String btAddr) throws JSONException {
        List<DeviceBean> list = MeshService.getInstance().API_get_list();
        DeviceBean device = null;
        for (DeviceBean item : list) {
            if (btAddr.equals(item.getBtAddrStr())) {
                device = item;
            }
        }
        return device;
    }

    void requestPermission(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            cordova.getActivity()
                    .requestPermissions(new String[] { WRITE_EXTERNAL_STORAGE, BLUETOOTH, BLUETOOTH_ADMIN,
                            BLUETOOTH_PRIVILEGED, ACCESS_NETWORK_STATE, ACCESS_COARSE_LOCATION, ACCESS_FINE_LOCATION,
                            MOUNT_UNMOUNT_FILESYSTEMS, READ_EXTERNAL_STORAGE, INTERNET }, 10000);
        }
        callbackContext.success();
    }

    // 初始化连接
    void init(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        MeshService.getInstance().API_register_mesh_callback(mcallback);
        MeshService.getInstance().API_register_mesh_data_channel((byte)0xfb);
        callbackContext.success();
    }

    // 销毁连接
    void destroy(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        MeshService.getInstance().API_exit_mesh();
        callbackContext.success();
    }

    // 创建蓝牙网络
    void createOrLoginWifi(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        String wifi = args.getString(0);
        String password = args.getString(1);
        String rssi_tmp = "80";
        if (4 != wifi.length() || 4 != password.length()) {
            return;
        }

        byte[] homeId = BleUtil.int2byte(Integer.parseInt(wifi));
        byte[] pwd = password.getBytes();
        byte rssi = (byte) (Integer.parseInt(rssi_tmp) & 0xff);
        MeshService.getInstance().API_set_mesh_info(homeId, pwd, (byte)-rssi);
        callbackContext.success();
    }

    // 扫描附近蓝牙网络
    void scanWifi(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        boolean isEnable = args.getBoolean(0);
        MeshService.getInstance().API_scan_homeid(isEnable);
        callbackContext.success();
    }

    // 获取蓝牙网络id
    void getWifiNetIds(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        meshListenerCallback = callbackContext;
    }

    // 登录之后执行 网络加入
    void joinMesh(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        MeshService.getInstance().API_central_join_mesh();
        callbackContext.success();
    }

    // 网络退出
    void exitMesh(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        MeshService.getInstance().API_exit_mesh();
        callbackContext.success();
    }

    // ping网络下的设备
    void pingMesh(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        MeshService.getInstance().pingAll();
        callbackContext.success();
    }

    // 获取网络下设备列表
    void getWifiDeviceList(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        JSONObject response = new JSONObject();
        JSONArray devices = getDeviceList();
        response.put("deviceList", devices);
        callbackContext.success(response);
    }

    // 监听网络下设备列表的变化
    void listenerWifiJoinStatus(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        listenerWifiJoinStatusCallback = callbackContext;
    }

    // 扫描设备
    void scanDevice(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        boolean isEnable = args.getBoolean(0);
        MeshService.getInstance().API_scan_discoverable_dev(isEnable);
        if (isEnable) {
            scanDeviceCallback = callbackContext;
        } else {
            callbackContext.success();
        }
    }

    // 新增设备入网
    void addDevice(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        String btAddr = args.getString(0);
        MeshService.getInstance().API_add_device(btAddr);
        addDeviceCallback = callbackContext;
    }

    // 删除设备
    void deleteDevice(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        int index = args.getInt(0);
        DeviceBean deviceBean = MeshService.getInstance().API_get_list().get(index);
        byte[] target_vaddr = deviceBean.getvAddr();
        MeshService.getInstance().deleteDevice(target_vaddr);
        deleteDeviceCallback = callbackContext;
    }

    // 发送命令
    void sendCommand(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        String btAddr = args.getString(0);
        DeviceBean deviceBean = getDeviceIndexByBtAddr(btAddr);
        byte[] target_vaddr = deviceBean.getvAddr();
        String data = args.getString(1);
        MeshService.getInstance().vendorSend(target_vaddr, 0, (short)0, Util.hexStringToBytes(data));
        callbackContext.success();
    }

    // 重命名
    void rename(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        int index = args.getInt(0);
        DeviceBean deviceBean = MeshService.getInstance().API_get_list().get(index);
        byte[] target_vaddr = deviceBean.getvAddr();
        String data = args.getString(1);
        MeshService.getInstance().nameSet(target_vaddr, Util.toUtf8(data), MeshFunc.ACK_TYPE_REMOTE);
        callbackContext.success();
    }
}
