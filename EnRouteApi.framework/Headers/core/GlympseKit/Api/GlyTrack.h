//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyTrack : GlyCommon

- (int)length;

- (GlyCommon*)getLocations;

- (GlyCommon*)getNewLocations;

- (int)getDistance;

@end