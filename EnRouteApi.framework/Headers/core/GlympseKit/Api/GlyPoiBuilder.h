//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyPoiBuilder : GlyCommon

- (void)setLocation:(GlyLatLng*)location;

- (void)setAddress:(GlyAddress*)address;

- (void)setName:(NSString*)name;

- (void)setLabel:(NSString*)label;

- (void)setProviderId:(NSString*)providerId;

- (void)setExternalId:(NSString*)externalId;

- (GlyPoi*)getPoi;

@end