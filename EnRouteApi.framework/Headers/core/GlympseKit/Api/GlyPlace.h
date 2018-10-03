//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyPlace : GlyLatLng< GlyComparable >

- (NSString*)getName;

- (GlyPlace*)clone;

@end