//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyActiveAgentsManager : GlyCommon< GlySource >

- (BOOL)isStarted;

- (void)refresh;

- (GlyArray<GlyActiveAgent*>*)getActiveAgents;

- (GlyActiveAgent*)findActiveAgentByAgentId:(long long int)agentId;

- (void)registerActiveAgent:(GlyActiveAgent*)activeAgent;

- (void)startTracking:(GlyActiveAgent*)activeAgent;

- (void)stopTracking:(GlyActiveAgent*)activeAgent;

@end