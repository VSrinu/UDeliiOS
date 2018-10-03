//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyTaskManager : GlyCommon< GlySource >

- (void)refresh;

- (GlyArray<GlyTask*>*)getTasks;

- (GlyArray<GlyTask*>*)getPendingTasks;

- (GlyArray<GlyOperation*>*)getActiveOperations;

- (GlyTask*)findTaskById:(long long int)id;

- (GlyOperation*)findOperationByTicket:(GlyTicket*)ticket;

- (BOOL)startTaskWithGlyTask:(GlyTask*)task;

- (BOOL)startTaskWithGlyTask:(GlyTask*)task withInt:(int)duration;

- (BOOL)setTaskPhase:(GlyTask*)task phase:(NSString*)phase;

- (BOOL)completeOperation:(GlyOperation*)operation;

@end