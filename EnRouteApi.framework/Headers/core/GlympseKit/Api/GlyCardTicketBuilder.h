//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyCardTicketBuilder : GlyCommon

- (void)setTicket:(GlyTicket*)ticket;

- (void)addCardMember:(GlyCardMember*)member;

- (void)setReference:(NSString*)reference;

- (GlyCardTicket*)getCardTicket;

@end