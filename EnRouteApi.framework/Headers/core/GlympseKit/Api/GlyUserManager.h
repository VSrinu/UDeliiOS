//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyUserManager : GlyCommon

- (GlyUser*)getSelf;

- (GlyTrack*)getSelfTrack;

- (GlyArray<GlyUser*>*)getUsers;

- (void)enableSorting:(BOOL)enable;

- (BOOL)anyActive;

- (GlyArray<GlyUser*>*)getStandaloneUsers;

- (void)enablePersistence:(BOOL)enable;

- (void)setUserTrackingMode:(int)mode;

- (int)getUserTrackingMode;

- (int)startTracking:(GlyUser*)user;

- (int)stopTracking:(GlyUser*)user;

- (int)getNumTrackers:(GlyUser*)user;

- (void)startTrackingAll;

- (void)stopTrackingAll:(BOOL)forced;

- (BOOL)anyActiveTracked;

- (GlyUser*)findOrCreateUserByUserId:(NSString*)userId;

- (GlyUser*)findUserByUserId:(NSString*)userId;

- (GlyUser*)findUserByInviteCode:(NSString*)code;

- (GlyTicket*)findTicketByInviteCode:(NSString*)code;

@end