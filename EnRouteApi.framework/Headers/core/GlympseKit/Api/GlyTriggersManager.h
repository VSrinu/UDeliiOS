//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyTriggersManager : GlyCommon< GlyEventSink >

- (void)addLocalTrigger:(GlyTrigger*)trigger;

- (void)removeLocalTrigger:(GlyTrigger*)trigger;

- (GlyArray<GlyTrigger*>*)getLocalTriggers;

@end