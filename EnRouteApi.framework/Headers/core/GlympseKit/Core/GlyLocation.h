//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyLocation : GlyLatLng

- (BOOL)hasProvider;

- (BOOL)hasAltitude;

- (BOOL)hasBearing;

- (BOOL)hasSpeed;

- (BOOL)hasHAccuracy;

- (BOOL)hasVAccuracy;

- (BOOL)hasTime;

- (int)getProvider;

- (float)getAltitude;

- (float)getBearing;

- (float)getSpeed;

- (float)getHAccuracy;

- (float)getVAccuracy;

- (long long int)getTime;

- (GlyLocation*)clone;

- (float)distanceTo:(GlyLatLng*)dest;

- (float)bearingTo:(GlyLatLng*)dest;

@end