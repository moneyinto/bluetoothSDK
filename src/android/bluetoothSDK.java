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

    private CallbackContext unbindDeviceCallback;

    private CallbackContext bindDeviceProgressCallback;

    private CallbackContext meshListenerCallback;

    private MeshNetInfo MeshNet;

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

    private final PlSigMeshProxyCallback mSigMeshProxyCB = new PlSigMeshProxyCallback() {
        @Override
        public void onNodeResetStatus(final short src) {
            // 删除解绑回调 强制删除配置文件
            mService.delMeshNode(src);
            unbindDeviceCallback.success(src);
        }

        @Override
        public void onConfigComplete(int result, MeshNetInfo.MeshNodeInfo config_node, MeshNetInfo mesh) {
            if (result != Util.PL_EVT_CONFIG_SUCCESS) {
                String tmp = "";
                if (result == Util.PL_EVT_CONFIG_ERR_CID_PID) {
                    tmp = "ERR CID PID";
                } else if (result == Util.PL_EVT_CONFIG_ERR_MODELID_MISMATCH) {
                    tmp = "ERR MODEL";
                } else if (result == Util.PL_EVT_CONFIG_ERR_MODELID_MISMATCH) {
                    tmp = "ERR Connection";
                }
                Log.d("DDD_CONFIG_ERR", "------------------");
                return;
            }

            final String addr = config_node.uuid;

            if (Util.CONFIG_MODE_PROVISION_CONFIG_ONE_BY_ONE == mService.get_config_mode()) {
                Log.d("DDD_1", "---------------");
                // 配置完成
            }

            if (Util.CONFIG_MODE_PROVISION_ONE_BY_ONE == mService.get_config_mode()) {
                Log.d("DDD_2", "---------------");
            }

            try {
                JSONObject response = new JSONObject();
                response.put("progress", 100);
                bindDeviceProgressCallback.success(response);
            } catch (Exception e) {
                Log.e("", e.toString());
            }
        }

        @Override
        public void onVendorUartData(short src, byte[] data) {
            Log.d("", "onVendorUartData " + src + " " + Util.byte2HexStr(data));
        }

        @Override
        public void onMeshStatus(int status, String addr) {
            // 如何确认是否加入成功
            Log.w("EEE", "onMeshStatus " + status + "---" + addr);
            try {
                JSONObject response = new JSONObject();
                response.put("status", status);
                PluginResult result = new PluginResult(PluginResult.Status.OK, response);
                result.setKeepCallback(true);
                meshListenerCallback.sendPluginResult(result);
            } catch (Exception e) {
                Log.e("", e.toString());
            }
            switch (status) {
            case Util.PL_MESH_READY:
                // mesh_status_info = "Mesh Joined " + addr;

                if (mService.get_config_mode() == Util.CONFIG_MODE_PROVISION_ONE_BY_ONE) {
                    for (int i = 0; i < MeshNet.nodes.size(); i++) {
                        if (!MeshNet.nodes.get(i).configed) {
                            mService.configNode(MeshNet.nodes.get(i).element_list.get(0).element_addr);
                            return;
                        }
                    }
                }
                break;
            case Util.PL_MESH_JOIN_FAIL:
                // mesh_status_info = "Mesh Join Fail";

                break;
            case Util.PL_MESH_EXIT:
                // mesh_status_info = "Mesh Exited";
                break;
            }
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
        public void onProvisionComplete(int result, MeshNetInfo.MeshNodeInfo provision_node, MeshNetInfo mesh) {
            Log.d("BBB", "onProvisionComplete " + result);
            Log.d("BBB", "onProvisionComplete " + provision_node);
            Log.d("BBB", "onProvisionComplete " + mesh);

            if (Util.CONFIG_MODE_PROVISION_ONE_BY_ONE == mService.get_config_mode()) {

            }
            if (Util.CONFIG_MODE_PROVISION_CONFIG_ONE_BY_ONE == mService.get_config_mode()) {

            }
            // 配置完成50%
            try {
                JSONObject response = new JSONObject();
                response.put("progress", 50);
                PluginResult progress = new PluginResult(PluginResult.Status.OK, response);
                progress.setKeepCallback(true);
                bindDeviceProgressCallback.sendPluginResult(progress);
            } catch (Exception e) {
                Log.e("", e.toString());
            }
        }

        @Override
        public void onAdvProvisionComplete(MeshNetInfo mesh, List<Util.AdvProvision> advProvisionList) {
            Log.d("CCC", "onProvisionComplete " + mesh);
        }
    };

    void addDev(BluetoothDevice dev) {
        for (int i = 0; i < devices.size(); i++) {
            if (devices.get(i).getAddress().equals(dev.getAddress()))
                return;
        }
        devices.add(dev);
    }

    void requestPermission(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            cordova.getActivity()
                    .requestPermissions(new String[] { WRITE_EXTERNAL_STORAGE, BLUETOOTH, BLUETOOTH_ADMIN,
                            BLUETOOTH_PRIVILEGED, ACCESS_NETWORK_STATE, ACCESS_COARSE_LOCATION, ACCESS_FINE_LOCATION,
                            MOUNT_UNMOUNT_FILESYSTEMS, READ_EXTERNAL_STORAGE, INTERNET }, REQUEST_CODE);
        }
        callbackContext.success();
    }

    // 初始化连接
    void init(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        Intent intent = new Intent(cordova.getActivity().getApplicationContext(), PlSigMeshService.class);
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

        for (int i = 0; i < 16; i++) {
            netkey[i] = 0;
            appkey[i] = 0;
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
        // mesh_net.current_admin = PlSigMeshService.getInstance().current_admin;
        mesh_net.admin_nodes.clear();

        MeshNetInfo.AdminNodeInfo admin_node = new MeshNetInfo.AdminNodeInfo();
        // admin_node.uuid = mesh_net.current_admin;
        admin_node.name = "user";
        admin_node.addr = 0x7fff;
        mesh_net.admin_nodes.add(admin_node);
        PlSigMeshService.getInstance().addMeshNet(mesh_net);
        callbackContext.success();
    }

    // 获取蓝牙网络id
    void getWifiNetIds(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        JSONObject response = new JSONObject();
        if (null != mService) {
            mService.init(cordova.getActivity(), Util.DBG_LEVEL_WARN, Util.DBG_LEVEL_WARN);
            List<MeshNetInfo> tmp_mesh_list = mService.getMeshList();
            JSONArray jsonArray = new JSONArray();

            for (MeshNetInfo netId : tmp_mesh_list) {
                JSONObject netIdObj = new JSONObject();
                netIdObj.put("name", netId.name);
                // netIdObj.put("time", netId.current_admin);
                netIdObj.put("appKey", netId.appkey);
                netIdObj.put("netKey", netId.netkey);
                // netIdObj.put("uuid", netId.current_admin);
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
        MeshNet = mService.chooseMeshNet(index);
        callbackContext.success();
    }

    // 注册扫描设备回调
    void registerScanDevices(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        if (null != mService) {
            mService.registerProvisionCb(mSigMeshProvisionCB);
            registerScanDevicesCallback = callbackContext;
        }
    }

    // 取消注册扫描设备回调
    void unRegisterScanDevices(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        if (null != mService) {

        }
        callbackContext.success();
    }

    // 扫描设备
    void scanDevice(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        boolean isEnable = args.getBoolean(0);
        if (null != mService) {
            mService.scanDevice(isEnable, Util.SCAN_TYPE_PROVISION);
        }
        callbackContext.success();
    }

    // 添加设备
    void addDevice(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        JSONObject device = args.getJSONObject(0);
        for (int i = 0; i < devices.size(); i++) {
            if (devices.get(i).getAddress().equals(device.getString("address"))) {
                BluetoothDevice Unporvisioned_Dev = devices.get(i);
                byte[] info = Util.hexStringToBytes(device.getString("uuid"));
                byte ele_num = info[15];
                mService.startProvision(Unporvisioned_Dev, ele_num);
                bindDeviceProgressCallback = callbackContext;
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
        for (int i = 0; i < mesh_net.nodes.size(); i++) {
            MeshNetInfo.MeshNodeInfo node_temp = mesh_net.nodes.get(i);
            for (int j = 0; j < node_temp.element_list.size(); j++) {
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
        mService.resetNode((short) addr);
        unbindDeviceCallback = callbackContext;
    }

    // 强制解绑删除设备
    void forceDeleteDevice(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        int addr = args.getInt(0);
        mService.delMeshNode((short) addr);
        callbackContext.success(addr);
    }

    // 发送命令
    void sendCommand(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        int addr = args.getInt(0);
        String data = args.getString(1);
        mService.vendorUartSend((short) addr, Util.hexStringToBytes(data), Util.PL_DEFAULT_APP_KEY_INDEX);
        callbackContext.success();
    }

    // proxy join 设备 (join 之前需要执行 scan)
    void proxyJoin(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        mService.proxyJoin();
        callbackContext.success();
    }

    // proxy exit 设备
    void proxyExit(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        mService.proxyExit();
        callbackContext.success();
    }

    // test on light
    void onLight(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        int addr = args.getInt(0);
        mService.setOnoff((short) addr, Util.PL_SIG_ONOFF_SET_ON, Util.PL_DEFAULT_ONOFF_TRANSITIONTIME,
                Util.PL_DEFAULT_ONOFF_DELAY, Util.PL_DEFAULT_APP_KEY_INDEX, true);
        callbackContext.success();
    }

    // test off light
    void offLight(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        int addr = args.getInt(0);
        mService.setOnoff((short) addr, Util.PL_SIG_ONOFF_SET_OFF, Util.PL_DEFAULT_ONOFF_TRANSITIONTIME,
                Util.PL_DEFAULT_ONOFF_DELAY, Util.PL_DEFAULT_APP_KEY_INDEX, true);
        callbackContext.success();
    }

    // 获取网络配置信息
    void getWifiJson(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        int index = args.getInt(0);
        String JsonString = mService.getJsonStrMeshNet(index);
        callbackContext.success(JsonString);
    }

    // 更新网络配置信息
    void updateWifiJson(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        String JSONString = args.getString(0);
        mService.updateJsonStrMeshNet(JSONString);
        callbackContext.success();
    }

    // 网络设备监听回调
    void wifiListener(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        meshListenerCallback = callbackContext;
    }
}
