//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlySessionManager : GlyCommon< GlySource >

- (BOOL)isStarted;

- (void)refresh;

- (GlyArray<GlySession*>*)getSessions;

- (BOOL)anyActiveSessions;

- (void)startSession:(GlySession*)session;

- (void)completeSession:(GlySession*)session reason:(int)reason;

- (GlySession*)findSessionById:(long long int)sessionId;

- (void)updateSessionTasks:(GlySession*)session tasks:(GlyCommon*)tasks;

@end