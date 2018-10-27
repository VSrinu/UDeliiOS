//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyCardMember : GlyCommon< GlyEventSink >

- (BOOL)isSelf;

- (GlyCardMemberDescriptor*)getInviter;

- (NSString*)getInviteId;

- (GlyCardTicket*)getTicket;

- (GlyCardTicket*)getRequest;

- (GlyCardMemberState*)getState;

- (long long int)getCreatedTime;

- (long long int)getLastModifiedTime;

@end