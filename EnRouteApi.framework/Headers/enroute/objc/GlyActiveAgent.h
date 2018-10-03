//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyActiveAgent : GlyCommon

- (GlyAgent*)getAgent;

- (GlySession*)getSession;

- (long long int)getAgentId;

- (GlyTicket*)getTicket;

@end