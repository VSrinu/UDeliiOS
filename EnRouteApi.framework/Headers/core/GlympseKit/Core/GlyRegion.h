//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyRegion : GlyLatLng< GlyComparable,GlyPersistable >

- (double)getRadius;

- (double)getAccuracy;

- (NSString*)getId;

@end