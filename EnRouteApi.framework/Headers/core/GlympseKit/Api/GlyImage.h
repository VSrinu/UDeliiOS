//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyImage : GlyCommon< GlyEventSink >

- (int)getState;

- (NSString*)getUrl;

- (GlyDrawable*)getDrawable;

- (BOOL)load;

- (BOOL)unload;

@end