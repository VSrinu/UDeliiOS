//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyFavoritesManager : GlyCommon< GlyEventSink >

- (void)setDraft:(GlyTicket*)draft;

- (GlyTicket*)getDraft;

- (GlyArray<GlyTicket*>*)getFavorites;

- (void)addFavorite:(GlyTicket*)ticket;

- (GlyTicket*)findMatch:(GlyTicket*)ticket;

- (BOOL)hasFavorite:(GlyTicket*)ticket;

- (void)removeFavoriteWithInt:(int)index;

- (void)removeFavoriteWithGlyTicket:(GlyTicket*)ticket;

- (void)moveFavorite:(int)fromIndex toIndex:(int)toIndex;

- (void)updateFavorite:(GlyTicket*)ticket index:(int)index;

@end