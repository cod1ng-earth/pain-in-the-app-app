 ## Summary

Beaconinside Cordova SDK for Android &amp; iOS platform.

See also the documentation for the [native SDKs](https://github.com/beaconinside/sdks).

## Table of contents

* [Example app](#example)
* [Get the SDK](#get-sdk)
* [Integrate the SDK](#integrate-sdk)
* [Ask for location and notification permissions](#permissions)
* [Set up an account](#account)
* [FAQs & Guides](#faq)
* [Advanced features](#advanced-features)
   * [Callbacks with meta data](#callbacks)
   * [Access the API](#api)
   * [Handling notifications](#notifications)
   * [Background data refresh](#bg-fetch)


## <a id="example"></a>Example

You can easily set up a sample project. Make sure you have [Cordova](https://cordova.apache.org/#getstarted) installed.

```bash
cordova -v # Check your Cordova version.
cordova create BeaconinsideApp
cd BeaconinsideApp
cordova platform add android
cordova build android
cordova run android

cordova platform add ios
# Select a development team in the XCode project editor for code signing.
cordova build ios
cordova run ios
```

As a next step you should go through the [integration steps](#integrate-sdk).


## <a id="get-sdk"></a>Get the SDK

You can get the latest version from the [releases](https://github.com/beaconinside/cordova-sdk/releases) page or use the *master branch*.

The following native SDKs are provided:
* [Beaconinside SDK for Android](https://github.com/beaconinside/android-sdk)
* [Beaconinside SDK for iOS](https://github.com/beaconinside/ios-sdk)

For iOS the minimum deployment target is iOS 9, for Android it is minSdkVersion 14.

## <a id="integrate-sdk"></a>Integrate the SDK

Add the Beaconinside SDK as a Cordova plugin, either as a local plugin or via the Github reference.

If you use Cordova 7 use the following command to add the SDK.

```bash
cordova plugin add https://github.com/beaconinside/cordova-sdk --nofetch
```

If you use a version of Cordova below 7 remove the `--nofetch` command.
```bash
cordova plugin add https://github.com/beaconinside/cordova-sdk
```

Initialize the Beaconinside SDK with the `initBeaconinsideSDK()` method. See [account setup](#account) to get your own application token.

```js
onDeviceReady: function() {
  this.receivedEvent('deviceready');

  // OPTIONAL, better request permissions on your own.
  // Request needed location and notification permissions.
  window.beaconinsideRequestAuthorization();

  // Change YOUR_APP_TOKEN with your own token
  window.initBeaconinsideSDK("YOUR_APP_TOKEN");
}
```

Continue with the next section to ask for the user's permission to use the device's location and.

Go through the following optionals steps...
   * to receive notifications in the background - [Handling notifications](#notifications)
   * to receive new content updates in the background - [Background data refresh](#bg-fetch)

## <a id="permissions"></a>Ask for location and notification permissions

To receive local notifications on iOS, a permission is required beginning with iOS 8. See the [UserNotifications Framework](https://developer.apple.com/reference/usernotifications).

For the Beaconinside SDK to work, the app needs to be authorized to use the device's location in the background. 

The following helper method can be used to request the needed permissions but it's recommended that the app developer take care about this process.

```js
  window.beaconinsideRequestAuthorization();
```

Make sure that you have set the *NSLocationWhenInUseUsageDescription*, the *NSLocationAlwaysUsageDescription* and *NSLocationAlwaysAndWhenInUseDescription* value in the `/{project}/platforms/ios/{project}/Info.plist` with a short and friendly text why you are using location-based services. 

You can check the logfiles on Android if there are location errors.

```bash
adb logcat

# java.lang.SecurityException: Need ACCESS_COARSE_LOCATION or ACCESS_FINE_LOCATION permission to get scan results
```

A permission popup has to be presented to the user. On Android and iOS you can check the app settings in the system menu to verify what permissions have been granted.


## <a id="account"></a>Account setup

* Sign up for a [Beaconinside Account][dmp] to access the web and mobile dashboards to manage all beacons, geofences and proximity services.

* Add nearby beacons and/or geofences in *MANAGE* for initial testing. For beacons you should select the right vendor and UUID, Major and Minor values.

* Create a campaign with _All Beacons_ group selected and a notification text. Make sure the scheduling criteria are valid for today and the status is *Published*.

* Get your `Application Token` under `Account -> Applications`. It should be kept secret as it uniquely identifies your mobile application.


## <a id="faq"></a>FAQs & Guides

### Requirements

**iOS**

* [Sign up][dmp] for an application token
* iOS 8.0+

**Android**

* [Sign up][dmp] for an application token
* Android 2.3 (API Level 9) or above
* Beacon detection only works with Android 4.3 (API Level 18)
* Google Play services

### Usage Guides

* [Campaign Demo Guide](http://developers.beaconinside.com/docs/demoing-beacons-and-geofences)
* [Setting up a virtual beacon](http://developers.beaconinside.com/docs/virtual-ibeacon)
* [Getting started with geofencing](http://developers.beaconinside.com/docs/geofencing-getting-started)
* [Advantages SDK over API](http://developers.beaconinside.com/docs/sdk-vs-api-integration)
* [SDK battery drain analysis](http://developers.beaconinside.com/docs/sdk-battery-drain)
* [Apple iBeacon guide](https://developer.apple.com/ibeacon/)


## <a id="examples"></a>Advanced features

### <a id="callbacks"></a>Callbacks with meta data

The SDK broadcasts by default entry, exit and update events for beacon and geofence zones via the NSNotificationCenter on iOS or local broadcasts on Android. Update events are defined by proximity changes between immediate, near, far and rough distance changes +/- 10m.

Just add an observer with these notification names.

```
BeaconServiceRegionEnter
BeaconServiceRegionUpdate
BeaconServiceRegionExit

GeofenceServiceRegionEnter
GeofenceServiceRegionExit
```

The notifications dictionary include for beacons
`BeaconID, proximity UUID, major, minor, proximity and source`. The latter defaults to "com.beaconinside". For geofences it's `GeofenceID, latitude, longitude, radius and source`.

Custom meta data (e.g. internal venue or zone IDs) can be added in the web panel with key=value pairs for beacons and geofences.

For Cordova the easiest way is to use the *cordova-broadcaster plugin* (forked version because of a required bug fix).

```bash
cordova plugin add https://github.com/beaconinside/cordova-broadcaster
```

In you code you can now receive beacon and geofence events.

```js
onDeviceReady: function() {

   // Log output for testing
   var listener = function(data) {
     console.log("keys: " + Object.keys(data));
     console.log("values: " + Object.values(data));
   }

  window.broadcaster.addEventListener( "BeaconServiceRegionEnter", listener);
}
```

See also the log output for event notifications.

```bash
adb logcat
adb logcat | grep fireEvent
...
# 05-10 16:08:38.943   319   319 D CordovaWebViewImpl: >>> loadUrl(javascript:window.broadcaster.fireEvent( 'BeaconServiceRegionEnter', {"proximity":"near","rssi":-68,"uuid":"F0018B9B-7509-4C31-A905-1A27D39C003C","major":42209,"minor":12731} );)
```

### <a id="api"></a>Access the API

All data can be accessed via server-side APIs. Take a look at the [Beaconinside Developer Hub][dev-hub] for the Manager API and the Analytics API reference.


### <a id="notification"></a>Handling notifications

In order to handle your proximity campaign notifications even when the app is closed, you need to implement the following code in your native AppDelegate file within XCode:

```objective-c
-(void) application:(UIApplication *)application didReceiveLocalNotification:(UILocalNotification *)notification{
   NSNotificationCenter* nc = [NSNotificationCenter defaultCenter];
   [nc postNotificationName:@"BeaconServiceNotificationReceived" object:self userInfo:notification.userInfo];
}
```

And the notification listener to your index.js file:

```js
onDeviceReady: function() {

var beaconinsideNotificationListener = function(data) {
  window.beaconinsideHandleNotification(data);
}

window.broadcaster.addEventListener( "BeaconServiceNotificationReceived", beaconinsideNotificationListener);
}
```

### <a id="bg-fetch"></a>Background data refresh

New campaigns, beacon or geofence regions are loaded when the app is opened. To increase this interval the SDK can ask the server once a day to load new data. This background data refresh is automatically done in Android. On iOS the following steps are needed and you have to enable in the XCode app capabilities in background modes: `Background fetch`.

In order to perform background fetching install the following plugin:

```bash
cordova plugin add cordova-plugin-background-fetch
```

Add the following code in your index.js:

```js
onDeviceReady: function() {

  var Fetcher = window.BackgroundFetch;

  var fetchCallback = function() {  
    window.beaconinsidePerformFetchWithCompletionHandler();
    Fetcher.finish();
  }

  Fetcher.configure(fetchCallback, null, {});
}
```

## <a id="support"></a>Support

Just [drop us](mailto:support@beaconinside.com) a message if there are any issues or questions.

## License

Copyright (c) 2015-2018 Beaconinside GmbH. All rights reserved.

[dev-hub]: http://developers.beaconinside.com
[beaconinside]: https://www.beaconinside.com
[dmp]: https://dmp.beaconinside.com
