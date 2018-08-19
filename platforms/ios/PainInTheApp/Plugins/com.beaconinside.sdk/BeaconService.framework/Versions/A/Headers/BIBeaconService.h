//
//  BIBeaconService.h
//  BeaconService
//
//  Created by Cornelius Rabsch on 13.10.14.
//  Copyright (c) 2015 BEACONinside GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <UserNotifications/UserNotifications.h>
#import "BIBeaconServiceConfig.h"

/**
 The Beaconinside beacon service library
 */
@interface BIBeaconService : NSObject

/**
 Init beacon service with the Beaconinside API application token.
 The app token can be found in your account settings.
 
 @param token Application API token
 */
+ (void)initWithToken:(NSString*)token;


/**
 Init beacon service with the Beaconinside API application token.
 The app token can be found in your account settings.
 
 @param token Application API token
 @param config BeaconService configuration object for customization
 */
+ (void)initWithToken:(NSString *)token andConfig:(BIBeaconServiceConfig*)config;

/**
 Safely terminate the beacon service (i.e. stop all beacon and geofence monitoring)
 */
+ (void)terminate;

/**
 Trigger user permission popups.
 It's recommended to call location and notification permission popups on your own
 when the user is likely to accept it (i.e. not immediately on app start).
 */
+ (void)requestAuthorization;

/**
 Check if user has given all location and local notification permissions
 
 @return True if user has all required permissions
 */
+ (BOOL)isAuthorized;

/**
 Background fetch handler which should be called from AppDelegate
 to be in synch with location triggers.
 
 @param completionHandler Background fetch completion handler
 */
+ (void)performFetchWithCompletionHandler:(void(^)(UIBackgroundFetchResult))completionHandler;


/**
 Handle local notifications properly in foreground and background states
 
 @param userInfo The notification dictionary
 */
+ (void)handleNotificationUserInfo:(NSDictionary*)userInfo;
/**
 
 
 @param notification  A notification to be presented
 */
+ (void)handleUNNotification:(UNNotification*)notification;
/**
 

 @param notification  A notification to be presented
 */
+ (void)handleNotification:(UILocalNotification*)notification  __deprecated_msg("UILocalNotification is deprecated. Use UNNotification framework since iOS 10.");;
/**
 


 Return application API token which should be set in the initializer
 @return Application token
 */
+ (NSString*)token;

/**
 Capture conversion event from custom notification handling
 
 @param notificationID ID from the campaign notification dictionary
 @param at Timestamp as NSString from campaign notification dictionary
 */
+ (void)sendConversion:(NSString*)notificationID triggeredAt:(NSString*)at;

@end
