//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@protocol GlyEventSink< NSObject >

- (BOOL)addListener:(id<GlyEventListener>)listener;

- (BOOL)removeListener:(id<GlyEventListener>)listener;

- (GlyCommon *)getContext:(long long int)key;

@end
