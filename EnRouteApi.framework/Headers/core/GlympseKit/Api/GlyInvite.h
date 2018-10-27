//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyInvite : GlyCommon< GlyComparable >

- (int)getType;

- (NSString*)getSubtype;

- (NSString*)getName;

- (NSString*)getAddress;

- (void)setBrand:(NSString*)brand;

- (void)applyBrand:(NSString*)brand;

- (NSString*)getBrand;

- (void)setVisible:(BOOL)visible;

- (BOOL)isVisible;

- (BOOL)isCreateOnly;

- (void)setCreateOnly:(BOOL)createOnly;

- (NSString*)getCode;

- (NSString*)getReference;

- (void)setReference:(NSString*)reference;

- (NSString*)getUrl;

- (int)getState;

- (long long int)getCreatedTime;

- (long long int)getLastViewTime;

- (int)getViewers;

- (int)getViewing;

- (GlyInviteViewers*)getViewerUsers;

- (GlyInviteViewers*)getViewingUsers;

- (BOOL)initiateClientSideSend;

- (BOOL)completeClientSideSend:(BOOL)succeeded;

- (NSString*)getText;

- (void)setRequestTicket:(GlyTicket*)requestTicket;

- (GlyTicket*)getRequestTicket;

- (GlyServerError*)getError;

- (GlyInvite*)clone;

@end