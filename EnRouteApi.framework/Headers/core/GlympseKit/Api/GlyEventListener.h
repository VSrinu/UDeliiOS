//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@class GlyGlympse;

@protocol GlyEventListener< NSObject >

- (void)eventsOccurred:(GlyGlympse*)glympse
              listener:(int)listener
                events:(int)events
                object:(GlyCommon*)object;

@end
