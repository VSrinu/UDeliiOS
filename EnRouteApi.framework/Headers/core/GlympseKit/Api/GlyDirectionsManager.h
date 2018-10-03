//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyDirectionsManager : GlyCommon

- (void)enableActivityRecognition:(BOOL)enable;

- (BOOL)isActivityRecognitionEnabled;

- (int)getDeviceActivity;

- (BOOL)isDeviceStationary;

- (void)setTravelMode:(int)mode;

- (int)getTravelMode;

- (void)setEtaQueryMode:(int)mode;

- (int)getEtaQueryMode;

- (GlyDirections*)queryDirections:(GlyLatLng*)origin destination:(GlyLatLng*)destination travelMode:(int)travelMode;

@end