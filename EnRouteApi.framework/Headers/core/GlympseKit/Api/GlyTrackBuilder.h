//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyTrackBuilder : GlyCommon

- (void)addLocation:(GlyLocation*)location;

- (void)setSource:(int)source;

- (void)setDistance:(int)distance;

- (void)calculateDistance;

- (GlyTrack*)getTrack;

@end