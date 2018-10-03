//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyGlympseFactory : NSObject
{
}

+ (GlyApiStatus*)createApiStatus:(NSString*)server;

+ (GlyGlympse*)createGlympseWithNSString:(NSString*)server withNSString:(NSString*)apiKey;

+ (GlyGlympse*)createGlympseWithNSString:(NSString*)server withNSString:(NSString*)apiKey withNSString:(NSString*)prefix;

+ (GlyInvite*)createInviteWithInt:(int)type withNSString:(NSString*)name withNSString:(NSString*)address;

+ (GlyInvite*)createInviteWithInt:(int)type withNSString:(NSString*)subtype withNSString:(NSString*)name withNSString:(NSString*)address;

+ (GlyInvite*)createPublicInvite:(NSString*)name;

+ (GlyTicket*)createTicket:(int)duration message:(NSString*)message destination:(GlyPlace*)destination;

+ (GlyTicket*)createRequest:(GlyTicket*)requestTicket invite:(GlyInvite*)invite;

+ (GlyPlace*)createPlace:(double)latitude longitude:(double)longitude name:(NSString*)name;

+ (GlyAddress*)createAddress:(NSString*)line1 line2:(NSString*)line2 city:(NSString*)city state:(NSString*)state zip:(NSString*)zip country:(NSString*)country;

+ (GlyImage*)createImage:(GlyDrawable*)drawable;

+ (GlyPrimitive*)createFacebookAccountProfile:(NSString*)token;

+ (GlyPrimitive*)createTwitterAccountProfile:(NSString*)consumerKey consumerSecret:(NSString*)consumerSecret oauthToken:(NSString*)oauthToken oauthTokenSecret:(NSString*)oauthTokenSecret;

+ (GlyPrimitive*)createEvernoteAccountProfile:(NSString*)token;

+ (GlyPrimitive*)createGoogleAccountProfile:(NSString*)token;

+ (GlyPrimitive*)createPairingCodeProfile;

+ (GlyPrimitive*)createPhoneAccountProfile:(NSString*)phone;

+ (GlyPrimitive*)createEmailAccountProfile:(NSString*)email;

+ (GlyPrimitive*)createGoogleServerAuthorizationProfile:(NSString*)code;

+ (GlyTrackBuilder*)createTrackBuilder;

+ (GlyGeoTrigger*)createGeoTrigger:(NSString*)name autoSend:(BOOL)autoSend ticket:(GlyTicket*)ticket center:(GlyLatLng*)center radius:(double)radius transition:(int)transition;

+ (GlyChronoTrigger*)createChronoTrigger:(NSString*)name autoSend:(BOOL)autoSend ticket:(GlyTicket*)ticket fireTime:(long long int)fireTime;

+ (GlyEtaTrigger*)createEtaTrigger:(NSString*)name autoSend:(BOOL)autoSend ticket:(GlyTicket*)ticket threshold:(long long int)threshold transition:(int)transition etaTicket:(GlyTicket*)etaTicket;

+ (GlyCard*)createCard:(NSString*)typeId name:(NSString*)name;

+ (GlyCardTicketBuilder*)createCardTicketBuilder:(int)aspect;

+ (GlyCardInvite*)createCardInvite:(GlyInvite*)invite;

+ (GlyCardObjectPoi*)createCardObjectPoi:(GlyPoi*)poi;

+ (GlyCardObjectInvite*)createCardObjectInvite:(NSString*)inviteCode;

+ (GlyPoiBuilder*)createPoiBuilder;

+ (GlyPoiBuilder*)createPoiBuilderWithGlyPoi:(GlyPoi*)source;

@end