//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyHandoffManager : GlyCommon< GlyEventSink >

- (GlyHandoffProvider*)getHandoffProvider;

- (BOOL)forceHandoffProvider:(NSString*)providerId data:(GlyPrimitive*)data;

- (BOOL)disableHandoffProvider;

- (void)overrideProviderConfig:(NSString*)providerId config:(GlyPrimitive*)config;

@end