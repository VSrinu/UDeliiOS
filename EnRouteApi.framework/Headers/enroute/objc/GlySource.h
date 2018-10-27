//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@protocol GlySource< NSObject >

- (BOOL)addListener:(id<GlyListener>)listener;

- (BOOL)removeListener:(id<GlyListener>)listener;

@end
