//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyBatteryManager : GlyCommon< GlyEventSink >

- (BOOL)setBatteryLevels:(int)lowBatteryLevel goodBatteryLevel:(int)goodBatteryLevel;

- (BOOL)isBatteryLevelGood;

- (BOOL)isBatteryOk;

- (BOOL)isBatteryForce;

- (void)setBatteryForce;

- (BOOL)isWakeLockEnabled;

- (void)enableWakeLock:(BOOL)wakeLockEnabled;

@end