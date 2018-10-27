//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyNetworkManager : GlyCommon< GlyEventSink >

- (BOOL)isInitialDataReceived;

- (BOOL)isNetworkError;

- (int)getPushAvailability;

- (BOOL)issueHttpRequest:(GlyPrimitive*)request;

@end