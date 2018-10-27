//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef GLYMPSEFACTORY_H__GLYMPSE__
#define GLYMPSEFACTORY_H__GLYMPSE__

namespace Glympse 
{
    
/**
 * The GlympseFactory class provides factory methods for instantiating major 
 * Glympse API primitives and Glympse platform itself.
 */
class GlympseFactory
{
    private: GlympseFactory();

    /**
     * Creates an API status object that can be used to query the Glympse API availability.
     *
     * @param server Base server URL.
     */
    public: static GApiStatus createApiStatus(const GString& server);
    
    /**
     * @param server Base server URL.
     * @param apiKey Partner specific API key.
     */
    public: static GGlympse createGlympse(const GString& server, const GString& apiKey);    
    
    /**
     * Prefix allows to instantiate multiple instances of Glympse platform within the same applocation bundle.
     * Prefix is required to serialize configuration and credentials of each Glympse insatnce separately.
     *
     * Prefix is not serialized locally. It should be specified each time, when paltform is instantiated.
     * Moreover, the same prefix value should be used during each next run.
     *
     * @param server Base server URL.     
     * @param apiKey Partner specific API key.
     * @param prefix File system friendly unique instance identifier.
     */
    public: static GGlympse createGlympse(const GString& server, const GString& apiKey, const GString& prefix);
    
    /**
     * Constructs invite object based on type, name and address of the recipient.
     * Type is intended to identify delivery mechanism and pick appropriate side
     * to schedule invite delivery (client or server). Invite name should provide
     * human-readable invite information (like person name). Address should uniquely
     * identify recipient within type namespace (examples: phone number, email, etc).
     *
     * It is required to specify invite type explicitly in the following cases:
     * - GC::INVITE_TYPE_ACCOUNT
     * - GC::INVITE_TYPE_TWITTER
     * - GC::INVITE_TYPE_FACEBOOK
     * - GC::INVITE_TYPE_LINK
     * - GC::INVITE_TYPE_SHARE
     * - GC::INVITE_TYPE_CLIPBOARD
     * - GC::INVITE_TYPE_EVERNOTE
     * - GC::INVITE_TYPE_GROUP (when raw group name is specified or invite is sent to a private group).
     *
     * It is only possible to pass GC::INVITE_TYPE_UNKNOWN, if address field contains
     * - phone number,
     * - email address or
     * - public group name (with leading '!' or '#').
     * In this case invite type will be determined by the library. 
     *
     * Group invite is marked visible automatically, if address starts with '#'.
     *
     * Each invite type has specific requirements for name and address arguments.
     * - GC::INVITE_TYPE_ACCOUNT
     *   - name    (optional): Recipient Glympse nickname
     *   - address (required): Glympse user id
     * - GC::INVITE_TYPE_EMAIL
     *   - name    (optional): Recipient name
     *   - address (required): Email address
     * - GC::INVITE_TYPE_SMS
     *   - name    (optional): Recipient name
     *   - address (required): Phone number
     * - GC::INVITE_TYPE_TWITTER
     *   - name    (optional): Twitter name of signed in user with leading @
     *   - address (optional): Twitter user id or Twitter name with leading @
     * - GC::INVITE_TYPE_FACEBOOK
     *   - name    (optional): Facebook name of signed in user
     *   - address (optional): Facebook user id
     * - GC::INVITE_TYPE_LINK
     *   - name    (optional): Application specific invite display name
     *   - address (optional): Application specific invite address
     * - GC::INVITE_TYPE_GROUP
     *   - name    (optional): Application specific invite display name
     *   - address (required): Glympse private group id, or Glympse public group name
     * - GC::INVITE_TYPE_SHARE
     *   - name    (optional): Name of application
     *   - address (required): Signature of application
     * - GC::INVITE_TYPE_CLIPBOARD
     *   - name    : none
     *   - address : none
     * - GC::INVITE_TYPE_EVERNOTE
     *   - name    : none
     *   - address : none
     *
     * @return Invite object or NULL, if invite cannot be constructed.
     */
    public: static GInvite createInvite(int32 type, const GString& name, const GString& address);

    /**
     * Creates invite by specifying both type and subtype. 
     *
     * This override should be used for creating invites of type GC::INVITE_TYPE_APP 
     * for which subtype must be specified and identifies receiving application.
     *
     * @return Invite object or NULL, if invite cannot be constructed.
     */
    public: static GInvite createInvite(int32 type, const GString& subtype, const GString& name, const GString& address);
    
    /**
     * Creates an invite to be sent to public group.
     * Constructs invite of GC::INVITE_TYPE_GROUP type. Provided for convenience.
     *
     * Group invite is marked visible automatically, if address starts with '#'.
     *
     * @param name Public group name.
     * @return Invite object or NULL, if invite cannot be constructed.
     */
    public: static GInvite createPublicInvite(const GString& name);
        
    /**
     * Creates new ticket object, which is intended to be sent.
     *
     * @param duration Ticket duration in milliseconds. 
     * @param message Ticket message (optional).
     * @param destination Ticket destination (optional).     
     * @return Returns ticket object, which is ready to be sent. 
     */
    public: static GTicket createTicket(int32 duration, const GString& message, const GPlace& destination);

    /**
     * Submits a request invite to the server with the given desired request ticket.
     *
     * @param requestTicket Sample ticket that the request receiver will use to fill in ticket details.
     * @param invite Invite information to be used in creating the invite.
     * @return ticket sink which can be used to subscribe to invte created events.
     */
    public: static GTicket createRequest(const GTicket& requestTicket, const GInvite& invite);

    /**
     * Creates place object.
     */
    public: static GPlace createPlace(double latitude, double longitude, const GString& name);
    
    /**
     * Creates new address object.
     *
     * @param line1 The first line of the street address.
     * @param line2 The second line of the street address.
     * @param city The city in which this address is located.
     * @param state The state in which this address is located.
     * @param zip The zip code of this address.
     * @param country The country in which the address is located.
     * @return Address object.
     */
    public: static GAddress createAddress(const GString& line1, const GString& line2, const GString& city, const GString& state, const GString& zip, const GString& country);
    
    /**
     * Creates image object.
     */
    public: static GImage createImage(const GDrawable& drawable);
    
    /**
     * Creates a Facebook account profile with the specified token.
     *
     * @param token The Facebook access token.
     *
     * @returns A Facebook account profile.
     */
    public: static GPrimitive createFacebookAccountProfile(const GString& token);
    
    /**
     * Creates a Twitter account profile with the specified parameters.
     *
     * @param consumerKey The Twitter consumer key associated with the application.
     * @param consumerSecret The Twitter consumer secret associated with the application.
     * @param oauthToken The Twitter oAuth token.
     * @param oauthTokenSecret The Twitter oAuth token secret.
     *
     * @returns A Twitter account profile.
     */
    public: static GPrimitive createTwitterAccountProfile(const GString& consumerKey, const GString& consumerSecret,
        const GString& oauthToken, const GString& oauthTokenSecret);

    /**
     * Creates an Evernote account profile with the specified token.
     *
     * @param token The Evernote access token.
     *
     * @returns An Evernote account profile.
     */
    public: static GPrimitive createEvernoteAccountProfile(const GString& token);

    /**
     * Creates a Google+ account profile with the specified token.
     *
     * @note Logging in or linking with this type of Google+ account profile will, if successful,
     * properly result in associating the identity of the user on the third-party service with a
     * Glympse user account. However, because it does not authorize the Glympse server to refresh 
     * the provided access token for subsequent use, this will result in the Google+ linked account 
     * immediately and permanently being marked as GC::LINKED_ACCOUNT_STATUS_REFRESH_NEEDED.
     *
     * @param token The Google+ access token.
     * @returns A Google+ account profile.
     */
    public: static GPrimitive createGoogleAccountProfile(const GString& token);

    /**
     * Creates a Google+ server authorization profile with the specified server authorization code.
     *
     * @note Logging in or linking with this type of Google+ account profile will, if successful,
     * properly result in associating the identity of the user on the third-party service with a
     * Glympse user account. Furthermore, because it authorizes the Glympse server to act on behalf
     * of the user in the background and grants the server the ability to extend the lifetime of 
     * access tokens, the Google+ linked account will remain in the GC::LINKED_ACCOUNT_STATUS_OK
     * state unless the user manually revokes access. However, in order to perform this authorization,
     * both the client application and the Glympse server must be "siblings" belonging to the same
     * Google developer console project. Generally speaking, therefore, logging in or linking with 
     * this type of Google+ account profile will perpetually fail except for approved and properly
     * configured Glympse partners.
     *
     * @param code The Google+ server authorization code.
     * @returns A Google+ server authorization profile.
     */
    public: static GPrimitive createGoogleServerAuthorizationProfile(const GString& code);

    /**
     * Creates a pairing code profile.
     * @note Logging in with this type of profile will, if successful provide a pairing code which
     * must be passed to another logged in device. Account login will be completed once the other
     * device enters the pairing code.
     */
    public: static GPrimitive createPairingCodeProfile();
    
    /**
     * Creates phone account profile.
     *
     * @param phone Phone number to be confirmed.
     *
     * @returns Phone account profile.
     */
    public: static GPrimitive createPhoneAccountProfile(const GString& phone);
    
    /**
     * Creates email account profile.
     *
     * @param phone Email address to be confirmed.
     *
     * @returns Email account profile.
     */
    public: static GPrimitive createEmailAccountProfile(const GString& email);

    /**
     * Creates an object intended to populate ITrack with location data.
     *
     * @return Track builder object.
     */
    public: static GTrackBuilder createTrackBuilder();
    
    /**
     * Creates Geo trigger object.
     *
     * @return Geo trigger object.
     */
    public: static GGeoTrigger createGeoTrigger(const GString& name, bool autoSend, const GTicket& ticket, const GLatLng& center, double radius, int32 transition);
    
    /**
     * Creates Chrono trigger object. This trigger fires at a given point in time. Time is value is in reference to Glympse time (GGlympse::getTime())
     *
     * @return Chrono trigger object.
     */
    public: static GChronoTrigger createChronoTrigger(const GString& name, bool autoSend, const GTicket& ticket, int64 fireTime);
    
    /**
     * Creates ETA trigger object. This trigger fires when a ticket's ETA drops below or rises above a given value
     *
     * @return ETA trigger object.
     */
    public: static GEtaTrigger createEtaTrigger(const GString& name, bool autoSend, const GTicket& ticket, int64 threshold, int32 transition, const GTicket& etaTicket);

    /**
     * Creates an empty card object.
     */
    public: static GCard createCard(const GString& cardTypeId, const GString& name);
    
    /**
     * Creates a card object that wraps a POI.
     */
    public: static GCardObjectPoi createCardObjectPoi(const GPoi& poi);
    
    /**
     * Creates a card object that wraps a Invite Code.
     */
    public: static GCardObjectInvite createCardObjectInvite(const GString& inviteCode);

    /**
     * Creates an card ticket builder.
     */
    public: static GCardTicketBuilder createCardTicketBuilder(int32 aspect);

    /**
     * Creates an card invite.
     */
    public: static GCardInvite createCardInvite(const GInvite& invite);
    
    /**
     * Creates an object intended for building IPoi objects.
     *
     * @return PoiBuilder object.
     */
    public: static GPoiBuilder createPoiBuilder();
    
    /**
     * Creates an object intended for building a new POI based off of existing POI.
     *
     * @param source The source POI from which to draw initial values.
     * @return PoiBuilder object.
     */
    public: static GPoiBuilder createPoiBuilder(const GPoi& source);
};
    
}

#endif // !GLYMPSEFACTORY_H__GLYMPSE__
