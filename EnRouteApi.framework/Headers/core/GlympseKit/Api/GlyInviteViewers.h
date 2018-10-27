//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyInviteViewers : GlyCommon< GlyEventSink >

- (GlyArray<GlyInviteViewer*>*)getViewers;

- (GlyCommon*)getViewersIndex;

@end