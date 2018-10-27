//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@protocol GlyLocationListener< NSObject >

- (void)locationChanged:(GlyLocation*)location;

- (void)stateChanged:(int)state;

@end