//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@protocol GlySource;

@protocol GlyListener< NSObject >

- (void)eventsOccurred:(id<GlySource>)source
              listener:(int)listener
                events:(int)events
                param1:(GlyCommon*)param1
                param2:(GlyCommon*)param2;

@end
