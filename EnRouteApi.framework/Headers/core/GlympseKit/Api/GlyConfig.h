//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyConfig : GlyCommon< GlyEventSink >

- (void)setExpireOnArrival:(int)mode;

- (int)getExpireOnArrival;

- (void)setXoaProfile:(GlyPrimitive*)profile;

- (GlyPrimitive*)getXoaProfile;

- (void)allowLocationSharing:(BOOL)allow;

- (BOOL)isSharingLocation;

- (void)allowSpeedSharing:(BOOL)allow;

- (BOOL)isSharingSpeed;

- (void)setAutoWatchPublicGroup:(BOOL)watch;

- (BOOL)isPublicGroupAutoWatched;

- (void)setTrackTrimmingEnabled:(BOOL)enabled;

- (BOOL)isTrackTrimmingEnabled;

- (long long int)getTrackTrimLength;

- (long long int)getAccountCreationTime;

- (long long int)getInviteLifetime;

- (int)getMaximumTicketDuration;

- (int)getPostRatePeriod;

- (int)getMaximumNicknameLength;

- (NSString*)getDeviceId;

- (BOOL)setDirectionsProvider:(GlyPrimitive*)provider;

- (GlyPrimitive*)getDirectionsProvider;

- (void)setCardsEnabled:(BOOL)enabled;

- (BOOL)areCardsEnabled;

- (void)setPoisEnabled:(BOOL)enabled;

- (BOOL)arePoisEnabled;

- (GlyPrimitive*)getContents;

- (void)save;

- (void)setDebug:(BOOL)debug;

- (BOOL)isDebug;

@end