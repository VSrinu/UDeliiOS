//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyTravelMode : GlyCommon< GlyComparable,GlyPersistable >

- (int)getMode;

- (GlyPrimitive*)getSettings;

@end