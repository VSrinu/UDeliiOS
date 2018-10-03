//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyDirections : GlyCommon< GlyEventSink >

- (int)getState;

- (long long int)getRequestTime;

- (GlyLatLng*)getOrigin;

- (GlyLatLng*)getDestination;

- (int)getTravelMode;

- (long long int)getEtaTs;

- (long long int)getEta;

- (GlyTrack*)getTrack;

@end