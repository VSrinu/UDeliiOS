//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyLinkedAccountsManager : GlyCommon< GlyEventSink >

- (BOOL)isSynced;

- (id<GlyEventSink>)confirm:(NSString*)type profile:(GlyPrimitive*)profile;

- (GlyLinkedAccount*)linkWithNSString:(NSString*)type withGlyPrimitive:(GlyPrimitive*)profile;

- (GlyLinkedAccount*)linkWithNSString:(NSString*)type withGlyPrimitive:(GlyPrimitive*)profile withBool:(BOOL)force;

- (GlyLinkedAccount*)unlink:(NSString*)type;

- (GlyLinkedAccount*)refreshWithNSString:(NSString*)type withGlyPrimitive:(GlyPrimitive*)profile;

- (GlyPrimitive*)getAccountProperty:(NSString*)type name:(NSString*)name;

- (void)setAccountProperty:(NSString*)type name:(NSString*)name value:(GlyPrimitive*)value;

- (GlyLinkedAccount*)getAccount:(NSString*)type;

- (GlyArray<GlyLinkedAccount*>*)getAccounts;

- (int)getCount:(BOOL)loginEnabled;

- (BOOL)refresh;

- (BOOL)canSend:(GlyInvite*)invite;

@end