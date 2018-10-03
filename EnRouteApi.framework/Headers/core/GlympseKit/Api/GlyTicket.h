//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyTicket : GlyCommon< GlyEventSink,GlyComparable >

- (NSString*)getId;

- (BOOL)isWatching;

- (BOOL)isMine;

- (BOOL)isSibling;

- (GlyPrimitive*)getVisibility;

- (BOOL)isVisible;

- (NSString*)getCode;

- (NSString*)getReference;

- (int)getState;

- (GlyAppProfile*)getOwner;

- (GlyUser*)getUser;

- (BOOL)isActive;

- (BOOL)isCompleted;

- (GlyArray<GlyInvite*>*)getInvites;

- (int)getDuration;

- (long long int)getStartTime;

- (long long int)getExpireTime;

- (NSString*)getMessage;

- (GlyPlace*)getDestination;

- (GlyTrack*)getTrack;

- (void)updateEta:(long long int)eta;

- (long long int)getEta;

- (void)updateRoute:(GlyTrack*)route;

- (GlyTrack*)getRoute;

- (GlyTravelMode*)getTravelMode;

- (GlyInvite*)findInviteByCode:(NSString*)code;

- (GlyInvite*)findInviteByAddress:(NSString*)address;

- (GlyInvite*)findInviteByType:(int)type;

- (BOOL)canAddInvite:(GlyInvite*)invite;

- (BOOL)addInvite:(GlyInvite*)invite;

- (BOOL)deleteInvite:(GlyInvite*)invite;

- (BOOL)isSomeoneWatching;

- (void)setRequestEndTime:(long long int)endTime;

- (GlyTicket*)getRequestTicket;

- (void)setRequestNoReply:(BOOL)requestNoReply;

- (BOOL)getRequestNoReply;

- (void)setRequestScenario:(NSString*)requestScenario;

- (NSString*)getRequestScenario;

- (BOOL)setVisibility:(NSString*)visibility context:(NSString*)context;

- (BOOL)modify:(int)remaining message:(NSString*)message destination:(GlyPlace*)destination;

- (BOOL)extend:(int)interval;

- (void)setName:(NSString*)name;

- (NSString*)getName;

- (BOOL)clear:(BOOL)message destination:(BOOL)destination;

- (BOOL)expire;

- (BOOL)appendData:(long long int)partnerId name:(NSString*)name value:(GlyPrimitive*)value;

- (GlyPrimitive*)getProperty:(long long int)partnerId name:(NSString*)name;

- (GlyDataRow*)getPropertyData:(long long int)partnerId name:(NSString*)name;

- (GlyCommon*)getPartnerData:(long long int)partnerId;

- (BOOL)own;

- (void)setOwnership:(NSString*)providerId providerData:(GlyPrimitive*)providerData;

- (BOOL)deleteTicket;

- (GlyTicket*)clone;

@end