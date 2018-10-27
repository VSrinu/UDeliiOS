//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyHistoryManager : GlyCommon

- (BOOL)isSynced;

- (GlyArray<GlyTicket*>*)getTickets;

- (BOOL)anyActive;

- (BOOL)anyActiveWithBool:(BOOL)siblings;

- (BOOL)anyActiveWithBool:(BOOL)siblings withBool:(BOOL)visible;

- (void)refresh;

- (void)simulateAddedEvents:(id<GlyEventListener>)listener;

- (BOOL)canSend:(GlyInvite*)invite;

- (void)enablePreSyncEvents:(BOOL)enable;

- (BOOL)arePreSyncEventsEnabled;

- (void)enableCancellationTimer:(BOOL)enable;

- (BOOL)isCancellationTimerEnabled;

- (void)setCancellationTimeout:(int)timeout;

- (int)getCancellationTimeout;

- (void)setExpirationMode:(int)mode;

- (int)getExpirationMode;

- (void)setXoAListener:(id<GlyXoAListener>)listener;

- (void)triggerXoAUpdate;

- (long long int)getLastViewTime;

- (BOOL)isSomeoneWatching;

- (GlyTicket*)findTicketByTicketId:(NSString*)ticketId;

- (GlyTicket*)findTicketByInviteCode:(NSString*)code;

@end