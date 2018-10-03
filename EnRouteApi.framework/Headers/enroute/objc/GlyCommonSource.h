//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyCommonSource : NSObject

#ifdef __cplusplus
- (id)initWithSink:(const Glympse::GSource&)source;
#endif

- (BOOL)addListener:(id<GlyListener>)listener;

- (BOOL)removeListener:(id<GlyListener>)listener;

@end
