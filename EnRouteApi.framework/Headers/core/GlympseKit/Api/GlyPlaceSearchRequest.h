//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyPlaceSearchRequest : GlyCommon

- (NSString*)getSearchTerm;

- (GlyLatLng*)getLocation;

- (NSObject*)getContext;

@end