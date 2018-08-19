package com.beaconinside.androidsdk;

import com.beaconinside.androidsdk.BeaconService;

import android.Manifest;
import android.content.pm.PackageManager;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaPlugin;
import org.json.JSONArray;
import org.json.JSONException;

public class SdkPlugin extends CordovaPlugin {

    /**
     * Executes the request and returns PluginResult.
     *
     * @param action          The action to execute.
     * @param args            JSONArry of arguments for the plugin.
     * @param callbackContext The callback context from which we were invoked.
     */
    public boolean execute(String action, final JSONArray args, final CallbackContext callbackContext) throws JSONException {
        if (action.equals("init")) {
            BeaconService.init(this.cordova.getActivity(), args.optString(0));
            return true;
        } else if (action.equals("beaconinsideRequestAuthorization")) {
            if (ContextCompat.checkSelfPermission(this.cordova.getActivity(), Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED) {
                ActivityCompat.requestPermissions(this.cordova.getActivity(),
                        new String[]{Manifest.permission.ACCESS_FINE_LOCATION}, 1);
            }
            return true;
        }
        return false;
    }

}
