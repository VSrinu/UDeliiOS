//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyEtaPlanner : GlyCommon< GlySource >

- (void)query:(GlyLatLng*)start stops:(GlyCommon*)stops stopoverTime:(long long int)stopoverTime;

- (void)abort;

- (void)stop;

@end