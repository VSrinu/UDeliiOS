//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyLocationProfileBuilder : GlyCommon

- (void)setMode:(int)mode;

- (void)setSource:(int)source;

- (void)setDistance:(double)distance;

- (void)setAccuracy:(double)accuracy;

- (void)setFrequency:(int)frequency;

- (void)setPriority:(int)priority;

- (void)setActivity:(int)activity;

- (void)setAutoPauseEnabled:(BOOL)enabled;

- (void)setSignificantLocationChangeMonitoringEnabled:(BOOL)enabled;

- (GlyLocationProfile*)getLocationProfile;

@end