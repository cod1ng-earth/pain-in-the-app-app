#import <Foundation/Foundation.h>
#import <Cordova/CDV.h>
#import <BeaconService/BIBeaconService.h>

@interface BeaconinsideSdkPlugin : CDVPlugin

- (void)init:(CDVInvokedUrlCommand *)command;
- (void)beaconinsideRequestAuthorization:(CDVInvokedUrlCommand *)command;
- (void)beaconinsidePerformFetchWithCompletionHandler:(CDVInvokedUrlCommand *)command;
- (void)beaconinsideHandleNotification:(CDVInvokedUrlCommand *)command;

@end

@implementation BeaconinsideSdkPlugin

- (void)init:(CDVInvokedUrlCommand *)command {
    NSString *appToken = command.arguments[0];
    [BIBeaconService initWithToken:appToken];
}

- (void)beaconinsideRequestAuthorization:(CDVInvokedUrlCommand *)command{
    [BIBeaconService requestAuthorization];
}

- (void)beaconinsidePerformFetchWithCompletionHandler:(CDVInvokedUrlCommand *)command{
    [BIBeaconService performFetchWithCompletionHandler:nil];
}

- (void)beaconinsideHandleNotification:(CDVInvokedUrlCommand *)command{
    
    NSDictionary *userInfoDict = command.arguments[0];
    [BIBeaconService handleNotificationUserInfo:userInfoDict];
}


@end
