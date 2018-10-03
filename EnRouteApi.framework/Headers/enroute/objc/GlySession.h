//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlySession : GlyCommon

- (long long int)getId;

- (long long int)getCreatedTime;

- (NSString*)getDescription;

- (GlyArray<GlyTask*>*)getTasks;

- (GlyTask*)getActiveTask;

- (int)getActiveTaskIndex;

- (int)getState;

- (long long int)getStartTime;

- (long long int)getOrgId;

- (long long int)getAgentId;

- (long long int)getOperationId;

- (GlyOperation*)getOperation;

- (int)getCompletionReason;

@end