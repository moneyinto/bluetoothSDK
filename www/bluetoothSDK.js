var BluetoothSDK = function () {};

BluetoothSDK.prototype.errorCallback = function (msg) {
  console.log('BluetoothSDK Callback Error: ' + msg)
}

BluetoothSDK.prototype.callNative = function (name, args, successCallback, errorCallback) {
    if (errorCallback) {
        cordova.exec(successCallback, errorCallback, 'BluetoothSDK', name, args)
    } else {
        cordova.exec(successCallback, this.errorCallback, 'BluetoothSDK', name, args)
    }
}

BluetoothSDK.prototype.requestPermission = function (successCallback, errorCallback) {
    this.callNative('requestPermission', [], successCallback, errorCallback);
}

BluetoothSDK.prototype.init = function (successCallback, errorCallback) {
    this.callNative('init', [], successCallback, errorCallback);
}

BluetoothSDK.prototype.destroy = function (successCallback, errorCallback) {
    this.callNative('destroy', [], successCallback, errorCallback);
}

BluetoothSDK.prototype.createOrLoginWifi = function (wifi, password, successCallback, errorCallback) {
    this.callNative('createOrLoginWifi', [wifi, password], successCallback, errorCallback);
}

BluetoothSDK.prototype.scanWifi = function (isEnable, successCallback, errorCallback) {
    this.callNative('scanWifi', [isEnable], successCallback, errorCallback);
}

BluetoothSDK.prototype.getWifiNetIds = function (successCallback, errorCallback) {
    this.callNative('getWifiNetIds', [], successCallback, errorCallback);
}

BluetoothSDK.prototype.joinMesh = function (successCallback, errorCallback) {
    this.callNative('joinMesh', [], successCallback, errorCallback);
}

BluetoothSDK.prototype.exitMesh = function (successCallback, errorCallback) {
    this.callNative('exitMesh', [], successCallback, errorCallback);
}

BluetoothSDK.prototype.pingMesh = function (successCallback, errorCallback) {
    this.callNative('pingMesh', [], successCallback, errorCallback);
}

BluetoothSDK.prototype.listenerWifiJoinStatus = function (successCallback, errorCallback) {
    this.callNative('listenerWifiJoinStatus', [], successCallback, errorCallback);
}

BluetoothSDK.prototype.getWifiDeviceList = function (successCallback, errorCallback) {
    this.callNative('getWifiDeviceList', [], successCallback, errorCallback);
}

BluetoothSDK.prototype.scanDevice = function (isEnable, successCallback, errorCallback) {
    this.callNative('scanDevice', [isEnable], successCallback, errorCallback);
}

BluetoothSDK.prototype.addDevice = function (btAddr, successCallback, errorCallback) {
    this.callNative('addDevice', [btAddr], successCallback, errorCallback);
}

BluetoothSDK.prototype.deleteDevice = function (index, successCallback, errorCallback) {
    this.callNative('deleteDevice', [index], successCallback, errorCallback);
}

BluetoothSDK.prototype.sendCommand = function (index, command, successCallback, errorCallback) {
    this.callNative('sendCommand', [index, command], successCallback, errorCallback);
}

BluetoothSDK.prototype.rename = function (index, name, successCallback, errorCallback) {
    this.callNative('rename', [index, name], successCallback, errorCallback);
}

if (!window.BluetoothSDK) {
  window.BluetoothSDK = new BluetoothSDK();
}

module.exports = new BluetoothSDK()
