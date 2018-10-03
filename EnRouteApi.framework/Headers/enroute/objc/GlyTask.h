//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyTask : GlyCommon

- (int)getState;

- (long long int)getId;

- (GlyOperation*)getOperation;

- (NSString*)getDescription;

- (long long int)getDueTime;

- (GlyTicket*)getTicket;

- (NSString*)getPhase;

- (NSString*)getForeignId;

- (GlyArray<GlyPrimitive*>*)getMetadata;

@end