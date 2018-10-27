//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyEnRouteManager : GlyCommon< GlySource >

- (NSString*)getSdkVersion;

- (void)setVersion:(NSString*)label version:(NSString*)version;

- (void)setBaseUrl:(NSString*)baseUrl;

- (NSString*)getBaseUrl;

- (void)setAuthenticationMode:(int)mode;

- (int)getAuthenticationMode;

- (void)registerDeviceToken:(NSString*)tokenType deviceToken:(NSString*)deviceToken;

- (void)handleRemoteNotification:(NSString*)payload;

- (BOOL)isLoginNeeded;

- (BOOL)loginWithCredentials:(NSString*)username password:(NSString*)password;

- (BOOL)loginWithToken:(NSString*)token expireTime:(long long int)expireTime;

- (void)logout:(int)reason;

- (BOOL)start;

- (void)stop;

- (BOOL)isStarted;

- (void)setActive:(BOOL)active;

- (BOOL)isActive;

- (void)refresh;

- (GlyOrganization*)getOrganization;

- (GlyAgent*)getSelfAgent;

- (GlyAgent*)getLoggedInAgent;

- (NSString*)getEnRouteToken;

- (GlyGlympse*)getGlympse;

- (GlyTaskManager*)getTaskManager;

- (GlyAgentManager*)getAgentManager;

- (GlySessionManager*)getSessionManager;

- (GlyActiveAgentsManager*)getActiveAgentsManager;

- (GlyEtaPlanner*)getEtaPlanner;

- (GlyDiagnosticsCollector*)getDiagnosticsCollector;

- (void)overrideLoggingLevels:(int)fileLogLevel debugLogLevel:(int)debugLogLevel;

@end