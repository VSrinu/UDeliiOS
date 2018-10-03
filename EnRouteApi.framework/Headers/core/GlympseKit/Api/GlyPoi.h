//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyPoi : GlyCommon

- (NSString*)getId;

- (GlyLatLng*)getLocation;

- (GlyAddress*)getAddress;

- (NSString*)getName;

- (NSString*)getLabel;

- (NSString*)getProviderId;

- (NSString*)getExternalId;

@end