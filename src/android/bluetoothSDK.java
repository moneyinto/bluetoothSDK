package com.jieweifu.bluetoothSDK;

import android.content.ServiceConnection;
import android.util.Log;

import org.apache.cordova.CordovaArgs;
import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.CallbackContext;

import org.json.JSONException;

import java.lang.reflect.Method;

/**
 * This class echoes a string called from JavaScript.
 */
public class bluetoothSDK extends CordovaPlugin {
    private PlSigMeshService mService = null;

    @Override
    public boolean execute(final String action, final CordovaArgs args, final CallbackContext callbackContext) throws JSONException {
        cordova.getThreadPool().execute(new Runnable() {
            @Override
            public void run() {
                try {
                    Method method = bluetoothSDK.class.getDeclaredMethod(action, CordovaArgs.class, CallbackContext.class);
                    method.invoke(bluetoothSDK.this, args, callbackContext);
                } catch (Exception e) {
                    Log.e("", e.toString());
                }
            }
        });
        return true;
    }

    public ServiceConnection mConnection = new ServiceConnection() {
		@Override
		public void onServiceConnected(ComponentName name, IBinder service) {
			Log.d(TAG, "PlSigMeshService ServiceConnected");
			PlSigMeshService.LocalBinder binder = (PlSigMeshService.LocalBinder) service;
			mService = binder.getService();
			if(null != mService){// && mService.init(getApplication())){
				mService.init(NetListActivity.this, true, Util.DBG_LEVEL_WARN);
				List<MeshNetInfo> tmp_mesh_list = mService.getMeshList();

                for(int i = 0; i < tmp_mesh_list.size(); i++){
                    mNetListAdapter.addNet(tmp_mesh_list.get(i).name);
                }
			}
		}

		@Override
		public void onServiceDisconnected(ComponentName name) {
			Log.d("", "PlSigMeshService onServiceDisconnected");
			mService = null;
		}
	};

    // 创建蓝牙网络
    void userLogin(CordovaArgs args, CallbackContext callbackContext) throws JSONException {
        String wifi = args.getString(0);
        if (8 != wifi.length()) {
            
            return;
        }

        homeId = wifi.getBytes();
        byte netkey[] = new byte[16];
        byte appkey[] = new byte[16];
        for(int i = 0;i < 16;i++){
            netkey[i]=0;
            appkey[i]=0;
        }

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
}
