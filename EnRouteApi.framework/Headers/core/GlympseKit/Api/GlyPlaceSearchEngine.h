//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyPlaceSearchEngine : GlyCommon< GlyEventSink >

- (GlyPlaceSearchRequest*)search:(NSString*)term location:(GlyLatLng*)location context:(NSObject*)context;

@end