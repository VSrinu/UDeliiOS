//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyCard : GlyCommon< GlyEventSink >

- (NSString*)getId;

- (NSString*)getTypeId;

- (NSString*)getName;

- (int)getState;

- (GlyCardMember*)getSelfMember;

- (GlyArray<GlyCardMember*>*)getMembers;

- (GlyCardMember*)findMemberByMemberId:(NSString*)id;

- (GlyCardMember*)findMemberByUserId:(NSString*)id;

- (GlyCardInvite*)findInviteByInviteId:(NSString*)id;

- (GlyArray<GlyCardInvite*>*)getInvites;

- (GlyArray<GlyCardObject*>*)getObjects;

- (GlyCardObject*)findObjectByObjectId:(NSString*)objectId;

- (GlyCardActivity*)getActivity;

- (long long int)getCreatedTime;

- (long long int)getLastModifiedTime;

- (BOOL)sendCardInvite:(GlyCardInvite*)invite;

- (BOOL)deleteCardInvite:(GlyCardInvite*)invite;

- (BOOL)acceptCardRequest:(GlyCardInvite*)request;

- (BOOL)deleteMember:(GlyCardMember*)member;

- (BOOL)updateName:(NSString*)name;

- (BOOL)startSharing:(GlyCardTicket*)cardTicket;

- (BOOL)stopSharing;

- (BOOL)shouldReply:(GlyCardTicket*)cardTicket;

- (BOOL)startRequesting:(GlyCardTicket*)cardTicket;

- (BOOL)stopRequesting;

- (BOOL)declineRequest:(GlyCardTicket*)cardTicket;

- (BOOL)isAcknowledged;

- (void)addObject:(GlyCardObject*)cardObject;

- (void)removeObject:(GlyCardObject*)cardObject;

- (void)createEvent:(NSString*)eventType data:(GlyPrimitive*)data;

@end