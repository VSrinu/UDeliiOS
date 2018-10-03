//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyOrgConfig : GlyCommon

- (GlyPrimitive*)asPrimitive;

- (NSString*)getBrandingId;

- (BOOL)shouldConfirmDuration;

- (long long int)getDefaultDuration;

- (BOOL)shouldAutoExtend;

- (BOOL)shouldShareSpeed;

- (BOOL)isPhaseSupportEnabled;

- (GlyCommon*)getPhaseConfigMap;

- (GlyArray<NSString*>*)getCompletionPhases;

- (BOOL)isSessionModeEnabled;

- (BOOL)shouldKeepLocationAlive;

- (long long int)getEtaQueryPeriod;

- (long long int)getStopDuration;

- (long long int)getActiveSessionTimeout;

- (BOOL)isDeviceSupportEnabled;

- (NSString*)getSessionControlMode;

- (BOOL)isRoutingEnabled;

- (GlyPrimitive*)getRoutingProfile;

- (long long int)getBaseGeofenceRadius;

- (long long int)getTaskGeofenceRadius;

- (GlyPrimitive*)getAdvancedXoaProfile;

- (BOOL)shouldCompleteArrivedTask;

- (BOOL)shouldAutoRefresh;

- (long long int)getAutoRefreshPeriod;

- (BOOL)shouldAutoFinish;

- (long long int)getAutoFinishDuration;

- (NSString*)getInitialPhase;

- (NSString*)getArrivalPhase;

- (NSString*)getFinalPhase;

- (BOOL)isVoipEnabled;

- (GlyPrimitive*)getVoipProfile;

@end