//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyCardTicket : GlyCommon

- (int)getAspect;

- (GlyTicket*)getTicket;

- (NSString*)getTicketId;

- (NSString*)getInviteCode;

- (GlyArray<GlyCardMemberDescriptor*>*)getCardMembers;

- (NSString*)getReference;

- (NSString*)getCardId;

- (NSString*)getCardMemberId;

- (long long int)getCreatedTime;

@end