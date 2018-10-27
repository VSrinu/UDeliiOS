//------------------------------------------------------------------------------
//
// Copyright (c) 2014 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#import <Foundation/Foundation.h>

@protocol GETListener <NSObject>

@optional

- (void)eventsOccurred:(const Glympse::GSource&)source listener:(Glympse::int32)listener events:(Glympse::int32)events param1:(const Glympse::GCommonObj&)param1 param2:(const Glympse::GCommonObj&)param2;

@end
