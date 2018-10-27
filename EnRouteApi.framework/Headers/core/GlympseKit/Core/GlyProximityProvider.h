//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@protocol GlyProximityProvider< NSObject >

- (void)setProximityListener:(id<GlyProximityListener>)proximityListener;

- (void)startMonitoringWithGlyRegion:(GlyRegion*)region;

- (void)startMonitoringWithGlyArray:(GlyArray<GlyRegion*>*)regions;

- (void)stopMonitoring:(GlyRegion*)region;

- (void)locationChanged:(GlyLocation*)location;

- (GlyArray<GlyRegion*>*)detachRegions;

@end