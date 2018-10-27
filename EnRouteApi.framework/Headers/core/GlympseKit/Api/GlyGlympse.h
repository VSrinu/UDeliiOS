//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyGlympse : GlyCommon< GlyEventSink >

- (id<GlyEventSink>)confirmAccount:(NSString*)type profile:(GlyPrimitive*)profile;

- (BOOL)login:(GlyPrimitive*)profile;

- (BOOL)logout;

- (void)start;

- (void)stop;

- (BOOL)isFirstLaunch;

- (BOOL)isStarted;

- (int)setActive:(BOOL)active;

- (BOOL)isActive;

- (NSString*)getAccessToken;

- (void)setHandler:(GlyHandler*)handler;

- (GlyHandler*)getHandler;

- (int)canDeviceSendSms;

- (void)setSmsSendMode:(int)smsSendMode;

- (int)getSmsSendMode;

- (void)enableSmsScraping:(BOOL)enable;

- (BOOL)isSmsScrapingEnabled;

- (void)setEtaMode:(int)etaMode;

- (int)getEtaMode;

- (void)setRestoreHistory:(BOOL)restore;

- (BOOL)isHistoryRestored;

- (void)setHistoryLookback:(long long int)interval;

- (long long int)getHistoryLookback;

- (void)allowSiblingTickets:(BOOL)allow;

- (BOOL)areSiblingTicketsAllowed;

- (void)enableInviteViewersTracking:(BOOL)enable;

- (BOOL)isInviteViewersTrackingEnabled;

- (BOOL)hasUserAccount;

- (void)setBrand:(NSString*)brand;

- (NSString*)getBrand;

- (void)enableApplicationsManager:(BOOL)enable;

- (BOOL)isApplicationsManagerEnabled;

- (NSString*)getBaseUrl;

- (NSString*)getApiKey;

- (NSString*)getPrefix;

- (GlyConfig*)getConfig;

- (GlyUserManager*)getUserManager;

- (GlyHistoryManager*)getHistoryManager;

- (GlyGroupManager*)getGroupManager;

- (GlyNetworkManager*)getNetworkManager;

- (GlyLocationManager*)getLocationManager;

- (GlyBatteryManager*)getBatteryManager;

- (GlyLinkedAccountsManager*)getLinkedAccountsManager;

- (GlyPairingManager*)getPairingManager;

- (GlyApplicationsManager*)getApplicationsManager;

- (GlyHandoffManager*)getHandoffManager;

- (GlyDirectionsManager*)getDirectionsManager;

- (id<GlySmsProvider>)getSmsProvider;

- (GlyTriggersManager*)getTriggersManager;

- (GlyPlaceSearchEngine*)getPlaceSearchEngine;

- (GlyFavoritesManager*)getFavoritesManager;

- (GlyCardManager*)getCardManager;

- (GlyPoiManager*)getPoiManager;

- (NSString*)cleanupInviteCode:(NSString*)code;

- (BOOL)compareInviteCodes:(NSString*)code1 code2:(NSString*)code2;

- (id<GlyEventSink>)decodeInviteWithNSString:(NSString*)code withInt:(int)mode;

- (id<GlyEventSink>)decodeInviteWithNSString:(NSString*)code withInt:(int)mode withGlyInvite:(GlyInvite*)invite;

- (BOOL)openUrl:(NSString*)message mode:(int)mode invite:(GlyInvite*)invite;

- (GlyArray<NSString*>*)extractInviteCodes:(NSString*)message;

- (int)getInviteAspect:(NSString*)code;

- (GlyImage*)createInviteSnapshot:(NSString*)invite parameters:(GlyPrimitive*)parameters style:(GlyPrimitive*)style;

- (GlyTicket*)viewTicket:(GlyUserTicket*)userTicket;

- (BOOL)sendTicket:(GlyTicket*)ticket;

- (void)requestTicket:(GlyTicket*)ticket;

- (void)verify;

- (long long int)getTime;

- (NSString*)getApiVersion;

- (NSString*)getApiVersionFull;

- (void)showDebugView;

- (void)overrideLoggingLevels:(int)fileLevel debugLevel:(int)debugLevel;

- (NSString*)getLogFile;

- (GlyArray<id<GlyEventSink>>*)findSinks:(id<GlyEventListener>)listener;

- (void)registerDeviceTokenWithNSString:(NSString*)deviceToken;

- (void)registerDeviceTokenWithNSString:(NSString*)tokenType withNSString:(NSString*)deviceToken;

- (void)unregisterDeviceToken;

- (void)unregisterDeviceTokenWithNSString:(NSString*)tokenType;

- (BOOL)hasValidDeviceToken;

- (BOOL)hasValidDeviceTokenWithNSString:(NSString*)tokenType;

- (void)handleRemoteNotificationWithNSString:(NSString*)payload;

- (void)handleRemoteNotificationWithNSString:(NSString*)payload withNSString:(NSString*)context;

- (void)enablePushEchoing:(BOOL)enable;

- (BOOL)isPushEchoingEbabled;

@end