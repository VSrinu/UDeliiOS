//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@protocol GlyProximityListener< NSObject >

- (void)regionEntered:(GlyRegion*)region;

- (void)regionLeft:(GlyRegion*)region;

@end