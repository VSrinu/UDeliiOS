//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyOperation : GlyCommon

- (int)getState;

- (long long int)getId;

- (long long int)getStartTime;

- (NSString*)getTicketId;

- (NSString*)getInviteUrl;

- (NSString*)getInviteCode;

- (long long int)getTaskId;

- (GlyTicket*)getTicket;

- (void)setTicketEta:(long long int)eta;

- (void)setTicketVisibile:(BOOL)visible;

- (BOOL)isTicketVisible;

- (void)applyTicketMetadata:(GlyArray<GlyPrimitive*>*)metadata;

@end