//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyTrigger : GlyCommon< GlyPersistable >

- (NSString*)getId;

- (NSString*)getName;

- (int)getType;

- (GlyTimeConstraint*)getTimeConstraint;

- (BOOL)autoSend;

- (GlyTicket*)getTicket;

@end