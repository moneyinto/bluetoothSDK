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

BluetoothSDK.prototype.createWifi = function (wifi, successCallback, errorCallback) {
    this.callNative('createWifi', [wifi], successCallback, errorCallback);
}

BluetoothSDK.prototype.getWifiNetIds = function (successCallback, errorCallback) {
    this.callNative('getWifiNetIds', [], successCallback, errorCallback);
}

BluetoothSDK.prototype.registerScanDevices = function (successCallback, errorCallback) {
    this.callNative('registerScanDevices', [], successCallback, errorCallback);
}

BluetoothSDK.prototype.unRegisterScanDevices = function (successCallback, errorCallback) {
    this.callNative('unRegisterScanDevices', [], successCallback, errorCallback);
}

BluetoothSDK.prototype.startScanDevice = function (successCallback, errorCallback) {
    this.callNative('startScanDevice', [], successCallback, errorCallback);
}

BluetoothSDK.prototype.addDevice = function (uuid, successCallback, errorCallback) {
    this.callNative('addDevice', [uuid], successCallback, errorCallback);
}

BluetoothSDK.prototype.registerAddProgress = function (successCallback, errorCallback) {
    this.callNative('registerAddProgress', [], successCallback, errorCallback);
}

BluetoothSDK.prototype.unRegisterAddProgress = function (successCallback, errorCallback) {
    this.callNative('unRegisterAddProgress', [], successCallback, errorCallback);
}

BluetoothSDK.prototype.sendCommand = function (command, successCallback, errorCallback) {
    this.callNative('sendCommand', [command], successCallback, errorCallback);
}

if (!window.BluetoothSDK) {
  window.BluetoothSDK = new BluetoothSDK();
}

module.exports = new BluetoothSDK()