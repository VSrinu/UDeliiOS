//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyAgentManager : GlyCommon< GlySource >

- (BOOL)isStarted;

- (void)refresh;

- (GlyArray<GlyAgent*>*)getAgents;

- (void)createAgent:(NSString*)username name:(NSString*)name password:(NSString*)password;

- (void)updateAgentName:(GlyAgent*)agent name:(NSString*)name;

- (void)updateAgentPassword:(GlyAgent*)agent password:(NSString*)password;

- (void)updateAgentAvatar:(GlyAgent*)agent drawable:(GlyDrawable*)drawable;

- (void)updateAgentRoles:(GlyAgent*)agent roles:(GlyArray<NSString*>*)roles;

- (void)updateAgentTags:(GlyAgent*)agent tags:(GlyArray<NSString*>*)tags;

- (void)deleteAgent:(GlyAgent*)agent;

- (void)submitAgentFeedback:(GlyPrimitive*)feedback;

- (GlyAgent*)findAgentById:(long long int)agentId;

@end