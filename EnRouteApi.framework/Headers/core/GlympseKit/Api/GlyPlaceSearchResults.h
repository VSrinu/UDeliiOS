//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyPlaceSearchResults : GlyCommon

- (GlyArray<GlyPlaceSearchResult*>*)getResults;

- (GlyPlaceSearchRequest*)getRequest;

@end