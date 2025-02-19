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

BluetoothSDK.prototype.createWifi = function (wifi, successCallback, errorCallback) {
    this.callNative('createWifi', [wifi], successCallback, errorCallback);
}

BluetoothSDK.prototype.getWifiNetIds = function (successCallback, errorCallback) {
    this.callNative('getWifiNetIds', [], successCallback, errorCallback);
}

BluetoothSDK.prototype.deleteWifiNetId = function (index, successCallback, errorCallback) {
    this.callNative('deleteWifiNetId', [index], successCallback, errorCallback);
}

BluetoothSDK.prototype.chooseWifiNetId = function (index, successCallback, errorCallback) {
    this.callNative('chooseWifiNetId', [index], successCallback, errorCallback);
}

BluetoothSDK.prototype.registerScanDevices = function (successCallback, errorCallback) {
    this.callNative('registerScanDevices', [], successCallback, errorCallback);
}

BluetoothSDK.prototype.unRegisterScanDevices = function (successCallback, errorCallback) {
    this.callNative('unRegisterScanDevices', [], successCallback, errorCallback);
}

BluetoothSDK.prototype.scanDevice = function (isEnable, successCallback, errorCallback) {
    this.callNative('scanDevice', [isEnable], successCallback, errorCallback);
}

BluetoothSDK.prototype.addDevice = function (device, successCallback, errorCallback) {
    this.callNative('addDevice', [device], successCallback, errorCallback);
}

BluetoothSDK.prototype.getDeviceList = function (index, successCallback, errorCallback) {
    this.callNative('getDeviceList', [index], successCallback, errorCallback);
}

BluetoothSDK.prototype.deleteDevice = function (addr, successCallback, errorCallback) {
    this.callNative('deleteDevice', [addr], successCallback, errorCallback);
}

BluetoothSDK.prototype.forceDeleteDevice = function (addr, successCallback, errorCallback) {
    this.callNative('forceDeleteDevice', [addr], successCallback, errorCallback);
}

BluetoothSDK.prototype.registerAddProgress = function (successCallback, errorCallback) {
    this.callNative('registerAddProgress', [], successCallback, errorCallback);
}

BluetoothSDK.prototype.unRegisterAddProgress = function (successCallback, errorCallback) {
    this.callNative('unRegisterAddProgress', [], successCallback, errorCallback);
}

BluetoothSDK.prototype.sendCommand = function (index, command, successCallback, errorCallback) {
    this.callNative('sendCommand', [index, command], successCallback, errorCallback);
}

BluetoothSDK.prototype.proxyJoin = function (successCallback, errorCallback) {
    this.callNative('proxyJoin', [], successCallback, errorCallback);
}

BluetoothSDK.prototype.proxyExit = function (successCallback, errorCallback) {
    this.callNative('proxyExit', [], successCallback, errorCallback);
}

BluetoothSDK.prototype.onLight = function (addr, successCallback, errorCallback) {
    this.callNative('onLight', [addr], successCallback, errorCallback);
}

BluetoothSDK.prototype.offLight = function (addr, successCallback, errorCallback) {
    this.callNative('offLight', [addr], successCallback, errorCallback);
}

BluetoothSDK.prototype.getWifiJson = function (addr, successCallback, errorCallback) {
    this.callNative('getWifiJson', [addr], successCallback, errorCallback);
}

BluetoothSDK.prototype.updateWifiJson = function (json, successCallback, errorCallback) {
    this.callNative('updateWifiJson', [json], successCallback, errorCallback);
}

BluetoothSDK.prototype.wifiListener = function (successCallback, errorCallback) {
    this.callNative('wifiListener', [], successCallback, errorCallback);
}

BluetoothSDK.prototype.isEnabled = function (successCallback, errorCallback) {
    this.callNative('isEnabled', [], successCallback, errorCallback);
}

if (!window.BluetoothSDK) {
  window.BluetoothSDK = new BluetoothSDK();
}

module.exports = new BluetoothSDK()
