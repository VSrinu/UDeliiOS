//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyHandler : GlyCommon

- (void)post:(id<GlyRunnable>)task;

- (void)postDelayed:(id<GlyRunnable>)task delayMillis:(long long int)delayMillis;

- (void)cancel:(id<GlyRunnable>)task;

- (BOOL)isMainThread;

@end