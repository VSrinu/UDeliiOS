//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyPlaceSearchResult : GlyCommon

- (GlyLatLng*)getLocation;

- (NSString*)getName;

- (NSString*)getAddress;

- (NSString*)getUrl;

- (GlyImage*)getIcon;

- (GlyArray<NSString*>*)getPhoneNumberTypes;

- (GlyArray<NSString*>*)getPhoneNumbers;

@end