//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyDataEvent : GlyCommon

- (GlyTicket*)getTicket;

- (GlyArray<GlyDataRow*>*)getProperties;

@end