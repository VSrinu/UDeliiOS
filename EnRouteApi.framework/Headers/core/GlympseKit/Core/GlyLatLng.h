//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyLatLng : GlyCommon

- (BOOL)hasLocation;

- (double)getLatitude;

- (double)getLongitude;

- (int)getLatitudeE6;

- (int)getLongitudeE6;

@end