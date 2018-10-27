//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyCardManager : GlyCommon< GlyEventSink >

- (GlyArray<GlyCard*>*)getCards;

- (GlyCardType*)findCardTypeById:(NSString*)id;

- (GlyArray<GlyCardType*>*)getCardTypes;

- (BOOL)createCard:(GlyCard*)card;

- (BOOL)joinCard:(GlyCard*)card;

- (GlyCard*)findCardByCardId:(NSString*)id;

- (GlyCardMember*)findCardMemberByTicketId:(NSString*)ticketId isSelf:(BOOL)isSelf;

- (BOOL)isSynced;

- (int)startTracking:(GlyCard*)card;

- (int)stopTracking:(GlyCard*)card;

- (int)getNumTrackers:(GlyCard*)card;

- (BOOL)anyActiveTracked;

@end