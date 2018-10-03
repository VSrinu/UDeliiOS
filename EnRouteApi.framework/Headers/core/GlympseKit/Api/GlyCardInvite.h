//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyCardInvite : GlyCommon< GlyEventSink >

- (long long int)getCreatedTime;

- (long long int)getLastModifiedTime;

- (NSString*)getId;

- (NSString*)getCardId;

- (GlyInvite*)getInvite;

- (GlyCardMemberDescriptor*)getInviter;

- (GlyCardMemberDescriptor*)getInvitee;

@end