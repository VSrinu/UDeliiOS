//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyLocationManager : GlyCommon< GlyEventSink >

- (GlyLocation*)getLocation;

- (int)startLocation;

- (int)stopLocation:(BOOL)forced;

- (void)setLocationProvider:(id<GlyLocationProvider>)locationProvider;

- (void)setProximityProvider:(id<GlyProximityProvider>)proximityProvider;

- (int)getLocationState;

- (void)enableProfiles:(BOOL)enable;

- (BOOL)areProfilesEnabled;

- (BOOL)updateProfile:(GlyLocationProfile*)profile;

- (GlyLocationProfile*)getCurrentProfile;

- (GlyLocationProfile*)getProfile:(int)profileId;

- (void)enableFiltering:(BOOL)enable;

- (BOOL)isFilteringEnabled;

- (void)handleGeofence:(NSString*)regionId transition:(int)transition;

@end