package com.jieweifu.bluetoothSDK;

import android.bluetooth.BluetoothDevice;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Build;
import android.os.IBinder;
import android.util.Log;

import com.pairlink.sigmesh.lib.MeshNetInfo;
import com.pairlink.sigmesh.lib.PlSigMeshProvisionCallback;
import com.pairlink.sigmesh.lib.PlSigMeshProxyCallback;
import com.pairlink.sigmesh.lib.Util;
import com.pairlink.sigmesh.lib.PlSigMeshService;

import org.apache.cordova.CordovaArgs;
import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.CallbackContext;

import org.apache.cordova.PluginResult;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.List;
import java.lang.reflect.Method;

import static android.Manifest.permission.*;

/**
 * This class echoes a string called from JavaScript.
 */
public class BluetoothSDK extends CordovaPlugin {
    private PlSigMeshService mService = null;

    private CallbackContext registerScanDevicesCallback;

    private List<BluetoothDevice> devices = new ArrayList<>();

    private static int REQUEST_CODE = 10000;

    private static BluetoothSDK instance;

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

        private boolean onoff;//false off, true on
        private short level = 0;

        private boolean counter_enable = false;
        private int counter;
        private long msg_transmit_time = 0;
    }
    
    @Override
    public boolean execute(final String action, final CordovaArgs args, final CallbackContext callbackContext) throws JSONException {
        cordova.getThreadPool().execute(new Runnable() {
            @Override
            public void run() {
                try {
                    Method method = BluetoothSDK.class.getDeclaredMethod(action, CordovaArgs.class, CallbackContext.class);
                    method.invoke(BluetoothSDK.this, args, callbackContext);
                } catch (Exception e) {
                    Log.e("", e.toString());
                }
            }
        });
        return true;
    }

    private final PlSigMeshProxyCallback mSigMeshProxyCB = new PlSigMeshProxyCallback() {
        @Override
        public void onNodeResetStatus(final short src){
            // 删除解绑回调 强制删除配置文件
            mService.delMeshNode(src);
        }
    };

    public ServiceConnection mConnection = new ServiceConnection() {
        @Override
        public void onServiceConnected(ComponentName name, IBinder service) {
            Log.d("", "PlSigMeshService ServiceConnected");
            PlSigMeshService.LocalBinder binder = (PlSigMeshService.LocalBinder) service;
            mService = binder.getService();
            mService.registerProxyCb(mSigMeshProxyCB);
        }

        @Override
        public void onServiceDisconnected(ComponentName name) {
            Log.d("", "PlSigMeshService onServiceDisconnected");
            mService = null;
        }
    };

    private final PlSigMeshProvisionCallback mSigMeshProvisionCB = new PlSigMeshProvisionCallback() {
        @Override
        public void onDeviceFoundUnprovisioned(final BluetoothDevice device, int rssi, final String uuid) {
            Log.d("AAA", "onDeviceFoundUnprovisioned");
            cordova.getActivity().runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    try {
                        Log.d("AAA", device.getAddress() + ", " + device.getName() + ", uuid:" + uuid);
                        addDev(device);
                        JSONObject response = new JSONObject();
                        response.put("address", device.getAddress());
                        response.put("name", device.getName());
                        response.put("uuid", uuid);
                        PluginResult result = new PluginResult(PluginResult.Status.OK, response);
                        result.setKeepCallback(true);
                        registerScanDevicesCallback.sendPluginResult(result);
                    } catch (Exception e) {
                        Log.e("", e.toString());
                    }
                }
            });
        }

        @Override
        public void onProvisionComplete(int result, MeshNetInfo.MeshNodeInfo provision_node, MeshNetInfo mesh){
            Log.d("BBB", "onProvisionComplete " + result);
            Log.d("BBB", "onProvisionComplete " + provision_node);
            Log.d("BBB", "onProvisionComplete " + mesh);
            if(Util.CONFIG_MODE_PROVISION_ONE_BY_ONE == mService.get_config_mode()) {

            }
            else if(Util.CONFIG_MODE_PROVISION_CONFIG_ONE_BY_ONE == mService.get_config_mode()){

            }
        }

        @Override
        public void onAdvProvisionComplete(MeshNetInfo mesh){
            Log.d("CCC", "onProvisionComplete " + mesh);
        }
    };

    void addDev(BluetoothDevice dev) {
        for(int i = 0; i < devices.size(); i++){
            if(devices.get(i).getAddress().equals(dev.getAddress()))
                return;
        }
        devices.add(dev);
    }

    void requestPermission(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
      if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
          cordova.getActivity().requestPermissions(new String[]{WRITE_EXTERNAL_STORAGE, BLUETOOTH, BLUETOOTH_ADMIN, BLUETOOTH_PRIVILEGED, ACCESS_NETWORK_STATE, ACCESS_COARSE_LOCATION, ACCESS_FINE_LOCATION, MOUNT_UNMOUNT_FILESYSTEMS, READ_EXTERNAL_STORAGE, INTERNET}, REQUEST_CODE);
      }
      callbackContext.success();
    }

    // 初始化连接
    void init(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        Intent intent= new Intent(cordova.getActivity().getApplicationContext(), PlSigMeshService.class);
        cordova.getActivity().bindService(intent, mConnection, Context.BIND_AUTO_CREATE);
        callbackContext.success();
    }

    // 销毁连接
    void destroy(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        cordova.getActivity().unbindService(mConnection);
        callbackContext.success();
    }

    // 创建蓝牙网络
    void createWifi(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        String wifi = args.getString(0);
        if (8 != wifi.length()) {
            
            return;
        }

        byte homeId[] = wifi.getBytes();
        byte netkey[] = new byte[16];
        byte appkey[] = new byte[16];

        for(int i = 0;i < 16;i++){
            netkey[i]=0;
            appkey[i]=0;
        }

        System.arraycopy(homeId, 0, netkey, 0, 4);
        System.arraycopy(homeId, 4, appkey, 0, 4);

        MeshNetInfo mesh_net = new MeshNetInfo();
        mesh_net.name = wifi;
        mesh_net.node_next_addr = 2;
        mesh_net.admin_next_addr = 0x7ffe;
        mesh_net.mesh_version = 0;
        mesh_net.gateway = false;
        mesh_net.netkey = Util.byte2HexStr(netkey);
        mesh_net.appkey = Util.byte2HexStr(appkey);
        mesh_net.iv_index = 0;
        mesh_net.seq = 1;
        mesh_net.nodes.clear();
        mesh_net.current_admin = PlSigMeshService.getInstance().current_admin;
        mesh_net.admin_nodes.clear();

        MeshNetInfo.AdminNodeInfo admin_node = new MeshNetInfo.AdminNodeInfo();
        admin_node.uuid = mesh_net.current_admin;
        admin_node.name = "user";
        admin_node.addr = 0x7fff;
        mesh_net.admin_nodes.add(admin_node);
        PlSigMeshService.getInstance().addMeshNet(mesh_net);
        callbackContext.success();
    }

    // 获取蓝牙网络id
    void getWifiNetIds(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        JSONObject response = new JSONObject();
        if(null != mService) {
            mService.init(cordova.getActivity(), true, Util.DBG_LEVEL_WARN);
            List<MeshNetInfo> tmp_mesh_list = mService.getMeshList();
            JSONArray jsonArray = new JSONArray();

            for(MeshNetInfo netId: tmp_mesh_list) {
                JSONObject netIdObj = new JSONObject();
                netIdObj.put("name", netId.name);
                netIdObj.put("time", netId.current_admin);
                netIdObj.put("appKey", netId.appkey);
                netIdObj.put("netKey", netId.netkey);
                netIdObj.put("uuid", netId.current_admin);
                jsonArray.put(netIdObj);
            }
            response.put("success", true);
            response.put("netIds", jsonArray);
            callbackContext.success(response);
        } else {
            response.put("success", false);
            callbackContext.success(response);
        }
    }

    // 删除蓝牙网络id
    void deleteWifiNetId(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        int index = args.getInt(0);
        PlSigMeshService.getInstance().deleteMeshNet(index);
        callbackContext.success();
    }

    // 选择蓝牙网络
    void chooseWifiNetId(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
      int index = args.getInt(0);
      mService.chooseMeshNet(index);
      callbackContext.success();
    }

    // 注册扫描设备回调
    void registerScanDevices(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        if(null != mService) {
            mService.registerProvisionCb(mSigMeshProvisionCB);
            registerScanDevicesCallback = callbackContext;
        }
    }

    // 取消注册扫描设备回调
    void unRegisterScanDevices(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        if(null != mService) {

        }
        callbackContext.success();
    }

    // 扫描设备
    void scanDevice(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        boolean isEnable = args.getBoolean(0);
        if(null != mService) {
            mService.scanDevice(isEnable, Util.SCAN_TYPE_PROVISION);
        }
        callbackContext.success();
    }

    // 添加设备
    void addDevice(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        JSONObject device = args.getJSONObject(0);
        for(int i = 0; i < devices.size(); i++){
            if(devices.get(i).getAddress().equals(device.getString("address"))) {
                BluetoothDevice Unporvisioned_Dev = devices.get(i);
                byte[] info = Util.hexStringToBytes(device.getString("uuid"));
                byte ele_num = info[15];
                mService.startProvision(Unporvisioned_Dev, ele_num);
                return;
            }
        }
    }

    // 获取设备列表
    void getDeviceList(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        int index = args.getInt(0);
        List<MeshDev> mesh_dev_list = new ArrayList<MeshDev>();
        MeshNetInfo mesh_net = mService.chooseMeshNet(index);
        JSONArray jsonArray = new JSONArray();
        for(int i = 0; i < mesh_net.nodes.size(); i++){
            MeshNetInfo.MeshNodeInfo node_temp = mesh_net.nodes.get(i);
            for(int j = 0; j < node_temp.element_list.size(); j++) {
                JSONObject netIdObj = new JSONObject();
                netIdObj.put("uuid", node_temp.uuid);
                netIdObj.put("name", node_temp.name);
                netIdObj.put("version", node_temp.version);
                netIdObj.put("addr", node_temp.primary_addr + j);
                jsonArray.put(netIdObj);
            }
        }
        JSONObject response = new JSONObject();
        response.put("deviceList", jsonArray);
        callbackContext.success(response);
    }

    // 解绑删除设备
    void deleteDevice(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        int addr = args.getInt(0);
        mService.resetNode((short)addr);
        callbackContext.success();
    }

    // 强制解绑删除设备
    void forceDeleteDevice(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        int addr = args.getInt(0);
        mService.delMeshNode((short)addr);
        callbackContext.success();
    }
}
