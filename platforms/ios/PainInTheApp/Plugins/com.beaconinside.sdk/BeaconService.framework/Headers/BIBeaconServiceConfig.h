//
//  BIBeaconServiceConfig.h
//  BeaconService
//
//  Created by Cornelius Rabsch on 14.05.16.
//  Copyright © 2016 Beaconinside GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>


@interface BIBeaconServiceConfig : NSObject

/**
 Designated initializer for configuration builder
 */
+ (BIBeaconServiceConfig*)defaultConfig;

/**
 Set a custom ID for your own reporting and analytics tasks.
 This can be a hashed email address or your own hashed user ids.
 Do not send personal identifiable information.
 
 @param identifier Your own user identifier
 */
- (void)setCustomID1:(NSString*)identifier;

/**
 Set another custom ID for your own reporting and analytics tasks.
 This can be a hashed email address or your own hashed user ids.
 Do not send personal identifiable information.
 
 @param identifier Your own user identifier
 */
- (void)setCustomID2:(NSString*)identifier;


/**
 Set context data to use custom targeting criteria that can be used to personalize the user experience.
 The block will be called by the SDK in background states, with or without internet and upon entering a beacon or geofence.

 @param block Block which is called to get dictionary with context params as key value pairs
 */
- (void)setContextDataHandler:(NSDictionary*(^)(void))block;

/**
 Configure beacon ranging interval, i.e. only capture
 beacon events every x seconds.
 
 @param interval Interval of beacon ranging events in seconds
 */
- (void)setBeaconRangingUpdateInterval:(NSUInteger)interval;


/**
 Read-only property to handle beacon ranging update interval
 */
@property (readonly, assign, nonatomic) NSUInteger beaconRangingUpdateInterval;


@end
