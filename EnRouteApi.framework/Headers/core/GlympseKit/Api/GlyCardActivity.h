//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyCardActivity : GlyCommon< GlyEventSink >

- (GlyArray<GlyCardEvent*>*)getEvents;

- (GlyCardEvent*)getMostRecentEvent;

- (NSString*)getCardId;

- (BOOL)isSynced;

@end