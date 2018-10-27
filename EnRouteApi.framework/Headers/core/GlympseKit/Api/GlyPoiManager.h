//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyPoiManager : GlyCommon< GlyEventSink >

- (BOOL)isSynced;

- (GlyArray<GlyPoi*>*)getPois;

- (void)addPoi:(GlyPoi*)poi;

- (void)updatePoi:(GlyPoi*)targetPoi sourcePoi:(GlyPoi*)sourcePoi;

- (void)removePoi:(GlyPoi*)poi;

- (GlyPoi*)findPoiById:(NSString*)poiId;

@end