//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IGLYMPSE_H__GLYMPSE__
#define IGLYMPSE_H__GLYMPSE__

namespace Glympse 
{
    
/**
 * The main Glympse API interface. In the Glympse system, a "Glympse" is referred to as a "ticket".  
 * The terms Ticket and Glympse should be considered equivalent in this documentation.
 */
/*O*public**/ struct IGlympse : public IEventSink
{
    /**
     * @name Life Cycle
     *
     * Methods to manipulate platform state.
     */
    
    /**
     * Sends confirmation code required to login with account of GC::LINKED_ACCOUNT_TYPE_PHONE of
     * GC::LINKED_ACCOUNT_TYPE_EMAIL type.
     *
     * Upon success, a GE::CONFIRMATION_CODE_SENT event is fired on LISTENER_CONFIRMATION_CODE.
     * Upon failure, a GE::CONFIRMATION_CODE_FAILED event is fired on LISTENER_CONFIRMATION_CODE.
     *
     * @param type The type of the account to be linked.
     * @param profile GPrimitive of CC#PRIMITIVE_TYPE_OBJECT type containing the profile
     * name and associated metadata. Use GlympseFactory static profile factory methods for
     * convenience.
     *
     * @return Event sink of GC::LISTENER_CONFIRMATION_CODE type.
     */
    public: virtual GEventSink confirmAccount(const GString& type, const GPrimitive& profile) = 0;
 
    /**
     * Provides the Glympse platform with an account profile and some metadata that can be used
     * to recover a user account. The account profile is propagated to the Glympse server for 
     * analysis, which usually involves validation using a 3rd-party service.
     *
     * @note The specified account profile is ignored if the platform already has a user account.
     * If hasUserAccount() returns true, call logout() first to clear out the existing account.
     *
     * @note This method must be called before the platform is started.
     *
     * @param profile GPrimitive of CC#PRIMITIVE_TYPE_OBJECT type containing the profile name and 
     * associated metadata. Use CoreFactory static profile factory methods for convenience.
     * 
     * @returns true if the operation succeeded, false otherwise
     */
	public: virtual bool login(const GPrimitive& profile) = 0;

    /**
     * Clears the existing user account in the Glympse platform if one exists. A new user account 
     * will be created during the next attempt to start the platform. To recover another user 
     * account, use login() to specify the profile of the account to recover before starting the 
     * platform again.
     *
     * @note This operation clears all user data (nickname, avatar, history, etc.).
     *
     * @note This method must be called while the platform is stopped.
     *
     * @returns true if the operation succeeded, false otherwise
     */
    public: virtual bool logout() = 0;
   
    /**
     * This starts the entire Glympse system.
     * This includes starting the Glympse service (to support background location sharing), starting the location manager,
     * loading persisted settings, and initiating communication with the Glympse server.
     * 
     * Note that certain properties can only be adjusted before platform is started. 
     * The following methods can only be called before platform is started:
     * - login()
     * - setHandler()
     * - enableSmsScraping()
     * - setEtaMode()
     * - setRestoreHistory()
     * - allowSiblingTickets()
     *
     * However, the majority of IGlympse methods should not be invoked before startup. 
     * All underlying managers are not accessible before platform is initialized. 
     * It is also impossible to send/view/request tickets.
     *
     * Glympse API performs authentication automatically upon successful startup. 
     * It also performs required synchronization with server upon successful authentication. 
     *
     * It is recommended you call the addListener() method before calling the start()
     * method in order to capture startup events.
     *
     * The counterpart to this method is the stop() method, which stops the Glympse system.
     */
    public: virtual void start() = 0;
    
    /**
     * This stops the entire Glympse system. This includes stopping the Glympse service, the location manager,
     * and shutting down communication with the Glympse server.
     *
     * Glympse object cannot be reused after it is stopped. New instance of Glympse platform
     * needs to be created every time when it is required to start platform.
     *
     * It is highly recommended to create single instance of Glympse platform per application launch.
     * This method should be called by host application when it is terminated by user or the OS. 
     *
     * @note The method cannot be called from within IEventListener::eventsOccurred().
     */
    public: virtual void stop() = 0;
    
    /**
     * This method determines whether or not this platform instance considers this to be first-launch instantiation.
     * That is, if the platform instance is created in an uninitialized, pristine environment. This method is valid
     * immediately after the platform is created and it's return value remains unchanged throughout the lifetime
     * thereof.
     *
     * @note Due to the criteria used to detect this condition, all calls to IGlympse::logout() will cause the return
     * value of this method to reset the next time a platform instance is instantiated.
     * 
     * @return true, if this platform instance was created in an uninitialized environment, false otherwise.
     */
    public: virtual bool isFirstLaunch() = 0;
    
    /**
     * @return true, if platform is started.
     */
    public: virtual bool isStarted() = 0;
    
    /**
     * Use this method to notify Glympse API when the application is going to the background or returns to the 
     * foreground. This method is backed by a reference count, so calls are expected to be reciprocal. When the 
     * reference count transitions from zero to one, the platform is activated; when the reference count transitions
     * from one to zero, the platform is deactivated. Note, however, that platform deactivation is not synchronous 
     * nor immediate; it is delayed for a short time in order to prevent premature deactivation in cases where it
     * will be reactivated quickly. In such cases, calls to reactivate the platform will cancel the deactivation and
     * the platform will remain active.
     *
     * @param active true, if the application has moved to the foreground, false if it has moved to the background.
     *
     * @return The active reference count. A reference count > zero means that the platform is [still] active. A 
     * reference count of zero means that the platform is, or will become, inactive.
     */
    public: virtual int32 setActive(bool active) = 0;
    
    /**
     * Gets platform state. 
     * 
     * @return Boolean value indicating whether platform is in active (foreground) state now. 
     */
    public: virtual bool isActive() = 0;
    
    /**
     * Exposes Glympse access token that library uses to authorize its requests to Glympse servers.
     *
     * The method can return NULL under certain circumstances. This effectively means that platform is 
     * in process of acquiring new token (assuming that it is up and running correctly).
     * In this case new token can be queried upon receiving GE#PLATFORM_LOGIN_SUCCEEDED event.
     *
     * Access token is short-lived. It is not supposed to be persisted on the application side or 
     * even cached in memory. Every time when host application needs to perform authenticated request
     * to Glympse servers it is supposed to query the token using this method.
     *
     * @return Glympse access token or NULL if platform is not started or not authenticated.
     */
    public: virtual GString getAccessToken() = 0;
    
    /**
     * @name Configuration
     *
     * Various tools to customize platform behavior.  
     */     
    
    /**
     * Allows to override concurrency layer. 
     *
     * Glympse API remains not thread safe in any case. By default it is only allowed to make calls to 
     * Glympse API methods on the thread, where it was instantiated. Moreover, this thread should be
     * event-driven thread and should be based on system run loop. This should not be necessarily main UI
     * thread, however. 
     * 
     * Providing custom handler implementation allows to instantiate Glympse API on a thread
     * with custom events processing mechanism.
     *
     * It is only allowed to invoke this method, when platform is yet started.
     * Handler is propagated through the hierarchy of API objects at startup. 
     *
     * @param handler Custom handler implementation. 
     */ 
    public: virtual void setHandler(const GHandler& handler) = 0;
    
    /**
     * Gets current concurrency layer. 
     *
     * @return Reference to current handler implementation. 
     */
    public: virtual GHandler getHandler() = 0;
    
    /**
     * Determines if the device can send SMS messages on its own.
     *
     * @return Returns on the following values:
     * - GC::SMS_SEND_AUTO if the device can send an SMS message programmatically (iPhone running iOS 4.x - 5.x; Android).
     * - GC::SMS_SEND_MANUAL if the device can send an SMS message via presenting standard UI (iPhone running iOS 6.0+).
     * - GC::SMS_SEND_NOT_SUPPORTED if the device can not send an SMS message (iPad/iPod; any Android device without SIM
     *   (including phone without SIM or coverage)). In this case Glympse API will still attempt to send SMS from server,
     *   but there is no guarantee, that SMS is sent (some restrictions apply).
     */
    public: virtual int32 canDeviceSendSms() = 0;
    
    /**
     * Configures the Glympse API to send SMS invites from the device's SMS number or from the Glympse server SMS provider.
     *
     * The Glympse API will attempt to detect the best method for sending SMS invites.
     * If the Glympse API believes the device can send SMS messages, it will send them
     * from the device's SMS number. Otherwise, it will send them from the Glympse server
     * SMS provider. See the canDeviceSendSms method for more information.
     *
     * The default mode (GC::SMS_SEND_MODE_DEFAULT) will perform this detection.
     * You may override this default behavior by setting the SMS send mode to GC::SMS_SEND_MODE_DEVICE or
     * GC::SMS_SEND_MODE_SERVER to force all SMS invites to be sent from the device or the server.
     */
    public: virtual void setSmsSendMode(int32 smsSendMode) = 0;
    
    /**
     * Queries the Glympse API for the current SMS send mode.
     * See the setSmsSendMode method for more information.
     *
     * @return The current SMS send mode.
     */
    public: virtual int32 getSmsSendMode() = 0;
    
    /**
     * Enables or disables automatic SMS scraping. SMS scraping is disabled by default.
     *
     * This method must be called before platform is started.
     *
     * This feature is only supported on Android and BB10.
     *
     * Android:
     *   It is required to add the following permission to AndroidManifest.xml:
     *   - <uses-permission android:name="android.permission.RECEIVE_SMS" />
     *
     * BB10:
     *   It is required to add the following permissions to bar-descriptor.xml:
     *   - <permission>access_sms_mms</permission>
     *   - <permission>access_pimdomain_messages</permission>
     */
    public: virtual void enableSmsScraping(bool enable) = 0;
    
    /**
     * Check if automatic SMS scraping is enabled.
     */
    public: virtual bool isSmsScrapingEnabled() = 0;
    
    /**
     * Allows to override default ETA mode. ETA mode defines, who is responsible for ETA calculation
     * (Glympse API or client application). By default Glympse API does not calculate ETA
     * (it operates in GC::ETA_MODE_EXTERNAL mode).
     *
     * Make sure that platform is not started yet, when making this call.
     * Otherwise it does not make any effect.
     *
     * @param etaMode New ETA mode. See GlympseConstants for details.
     */
    public: virtual void setEtaMode(int32 etaMode) = 0;
    
    /**
     * Queries the Glympse API for the current directions mode.
     * See the setDirectiosMode method for more information.
     *
     * @return The current ETA mode.
     */
    public: virtual int32 getEtaMode() = 0;
    
    /**
     * Specifies, whether expired tickets previously sent by the user should be
     * retrieved from server, when platform is started.
     *
     * Client API does not restores history by default. It only retrieves active tickets,
     * when platform is restarted.
     *
     * The method must be invoked before platform is started.
     * Property is not persisted across sessions.
     */
    public: virtual void setRestoreHistory(bool restore) = 0;
    
    /**
     * @return Indicates, whether history is restored from server, when platform is started.
     */
    public: virtual bool isHistoryRestored() = 0;
    
    /**
     * Sets interval of time that controls how far back in time to look for user's tickets.
     * All tickets returned by server will have
     * - TICKET_END_TIME >= ( NOW - INTERVAL )
     *
     * Client platform relies on default interval hardcoded on server side, 
     * if lookback interval is not specified by host application.
     * This essentially results into querying 30 days of user history.
     *
     * The method must be invoked before platform is started.
     * Property is not persisted across sessions.
     *
     * @param interval Interval of time in milliseconds or GC#HISTORY_LOOKBACK_DEFAULT.
     */
    public: virtual void setHistoryLookback(int64 interval) = 0;
    
    /**
     * Checks how far back in time serer should look when building a history list (accessible through
     * IHistoryManager#getTickets()).
     *
     * @return Interval of time in milliseconds or GC#HISTORY_LOOKBACK_DEFAULT. 
     */
    public: virtual int64 getHistoryLookback() = 0;
    
    /**
     * Enables sibling tickets. See Programming Guide for more details.
     * Sibling tickets are not requested from server by default.
     *
     * This method must be called before platform is started.
     */
    public: virtual void allowSiblingTickets(bool allow) = 0;
    
    /**
     * Checks whether sibling tickets are allowed.
     */
    public: virtual bool areSiblingTicketsAllowed() = 0;
    
    /**
     * Enables tracking of invite viewers. It is disabled by default.
     *
     * IInvite#getViewerUsers() and IInvite#getViewingUsers() are populated with users who ever viewed
     * and users who are currently viewing that particular invite.
     *
     * This method must be called before platform is started.
     * The setting is not persisted across sessions.
     */
    public: virtual void enableInviteViewersTracking(bool enable) = 0;
    
    /**
     * Checks to see if invite viewers tracking is enabled.
     *
     * @return true if platform is tracking invite viewers.
     */
    public: virtual bool isInviteViewersTrackingEnabled() = 0;
    
    /**
     * Checks to see if Glympse user account is already created (or imoprted).
     *
     * @return true, if platform already has an account.
     */
    public: virtual bool hasUserAccount() = 0;
    
    /**
     * Brand is subcategory of API key, which is used for additional customization
     * of outgoing invites (both invite messages and viewer experience).
     * API consumers can leverage it as extra hierarchy level under API key to
     * customize user experience.
     *
     * The method overrides global property, which is applied to all outgoing invites.
     * IInvite#setBrand can be used to modify the property for specific invite only.
     * Moreover, if brand is already set for an invite, it will not be overridden by
     * this global property.
     *
     * The method is optional. By default invites derive configuration from API key.
     */
    public: virtual void setBrand(const GString& brand) = 0;
    
    /**
     * Gets currently set brand or NULL, if brand is not set.
     */
    public: virtual GString getBrand() = 0;
    
    /**
     * Enables functionality exposed by IApplicationManager. 
     *
     * Application manager is disabled by default.
     */
    public: virtual void enableApplicationsManager(bool enable) = 0;
    
    /**
     * Checks if application manager is enabled.
     */
    public: virtual bool isApplicationsManagerEnabled() = 0;
    
    /**
     * Returns raw base URL without any suffixes.
     */
    public: virtual GString getBaseUrl() = 0;
    
    /**
     * Returns currently used API key.
     */
    public: virtual GString getApiKey() = 0;
    
    /**
     * Returns currently used prefix.
     */
    public: virtual GString getPrefix() = 0;
    
    /**
     * @name Child Components
     *
     * Glympse API object model is exposed to host applications through several components 
     * hidden behind faccade object (GGlympse).
     */
    
    /**
     * Gets platform configurator.
     *
     * @return The configurator object.
     */
    public: virtual GConfig getConfig() = 0;
    
    /**
     * Gets the user list.
     * The user list contains a collection of all the Glympse users that the client knows about.
     * This includes yourself, plus any users that you are watching via calls you have made to the viewTicket() method.
     * 
     * This list will initially just contain a single user representing yourself.
     * Once the Glympse API has communicated with the server, the list will be expanded to include the complete list 
     * of users you are currently watching.
     * 
     * To be notified when the list is first fully populated, you can register a IEventListener
     * and capture the GE#PLATFORM_USER_ADDED event.
     * 
     * To be notified any time this list changes or a user in the list changes,
     * you can register a IEventListener and capture the GE#PLATFORM_USER_LIST_CHANGED event.
     *
     * @return The user list object.
     */
    public: virtual GUserManager getUserManager() = 0;
    
    /**    
     * Gets your sent ticket list ("Glympse history").
     * The sent ticket list contains all the tickets you have created and sent.
     * This includes tickets that are still active as well as one that have expired.
     * 
     * This list will initially be empty. Once Glympse has communicated with the server,
     * the list will be populated to include the complete list of tickets you have sent.
     * 
     * To be notified when the list is first populated, you can register a IEventListener
     * and capture the PLATFORM_SYNCED_WITH_SERVER event.
     *
     * To be notified any time this list changes or a recipient in the list changes,
     * you can register a IEventListener and capture the PLATFORM_TICKET_LIST_CHANGED event.
     *
     * @return The sent ticket list object.
     */
    public: virtual GHistoryManager getHistoryManager() = 0;
    
    /**
     * Gets the group list.
     * The group list contains a collection of all the Glympse groups that the client participates at.
     *
     * @return The group list object.
     */
    public: virtual GGroupManager getGroupManager() = 0;        
    
    /**
     * Gets the network manager.
     *
     * @return The network manager object.
     */        
    public: virtual GNetworkManager getNetworkManager() = 0;    
    
    /**
     * Gets the location manager.
     *
     * @return The location manager object.
     */    
    public: virtual GLocationManager getLocationManager() = 0;
    
    /**
     * Gets the battery manager.
     *
     * @return The battery manager object.
     */
    public: virtual GBatteryManager getBatteryManager() = 0;  

    /**
     * Gets the linked accounts manager.
     *
     * @return The linked accounts manager object.
     */
    public: virtual GLinkedAccountsManager getLinkedAccountsManager() = 0;

    /**
     * Gets the pairing manager.
     *
     * @return The pairing manager object.
     */
    public: virtual GPairingManager getPairingManager() = 0;

    /**
     * Gets the applications manager.
     *
     * @return The applications manager object.
     */
    public: virtual GApplicationsManager getApplicationsManager() = 0;

    /**
     * Gets the handoff manager. 
     *
     * @return The handoff manager object.
     */
    public: virtual GHandoffManager getHandoffManager() = 0;
    
    /**
     * Gets the directions manager.
     *
     * @return The directions manager object.
     */
    public: virtual GDirectionsManager getDirectionsManager() = 0;
    
    /**
     * Provides access to SMS auto-send functionality. 
     */
    public: virtual GSmsProvider getSmsProvider() = 0;
    
    /**
     * Gets the triggers manager.
     *
     * @return The triggers manager object.
     */
    public: virtual GTriggersManager getTriggersManager() = 0;
    
    /**
     * Gets the place search engine.
     *
     * @return The place search engine.
     */
    public: virtual GPlaceSearchEngine getPlaceSearchEngine() = 0;

    /**
     * Gets favorites manager.
     *
     * @return The Favorites manager object.
     */
    public: virtual GFavoritesManager getFavoritesManager() = 0;

    /**
     * Gets card manager.
     *
     * @return The Card manager object. Will return NULL if the glympse platform is not started or if cards
     *     have not been enabled in the glympse configuration.
     */
    public: virtual GCardManager getCardManager() = 0;
    
    /**
     * Gets POI manager.
     *
     * @return The POI manager object. Will return NULL if the glympse platform is not started or if POIs
     *     have not been enabled in the glympse configuration.
     */
    public: virtual GPoiManager getPoiManager() = 0;

    /**
     * @name Invites Handling
     *
     * Tools for handling incoming ticket invites.
     */
    
    /**
     * Returns internal representation of valid invite code. The method gets rid of
     * dashes ('-') and other meaningless characters usually accompanying or being a
     * part of invite codes.
     *
     * Glympse API always stores and exposes cleaned up version of an invite code.
     *
     * @param code Invite code to be cleaned up.
     * @return Cleaned up invite code or NULL if code does not refer to an invite code.
     */
    public: virtual GString cleanupInviteCode(const GString& code) = 0;

    /**
     * Compares two invite codes and returns true if they are semantically identical
     * after normalizing and cleaning them.
     *
     * @param code1 The first invite code to compare.
     * @param code2 The second invite code to compare.
     * @return true, if the two invite codes are semantically equivalent; false otherwise.
     */
    public: virtual bool compareInviteCodes(const GString& code1, const GString& code2) = 0;
    
    /**
     * The method is provided for compatibility with old API versions.
     * See decodeInvite(GString, int32, GInvite) for more details. 
     */
    public: virtual GEventSink decodeInvite(const GString& code, int32 mode) = 0;
    
    /**
     * Decodes Glympse invite received via Email or SMS. Currently Glympse API
     * supports three types of invites:
     * - ticket invites;
     * - invites to groups;
     * - request invites. 
     *
     * Glympse invite URL has the following format:
     * http://glympse.com/XXX-XXX
     * A number of symbols before and after dash varies between 3 and 5. 
     * 
     * Invite is decoded asynchronously (this operation requires round trip to server).
     * 
     * The method returns even sink object, which is used to notify caller on invalid 
     * invite code (GE::INVITE_INVALID_CODE). 
     *
     * @param code Invite code to be verified. 
     * @param mode Bitmask used to configure method behaviour (see GC::INVITE_MODE_* for more details). 
     * @param invite Optional invite object, which is propagated all the way down to GC::PLATFORM_INVITE_* events.
     * The object is accessible through IUserTicket#getInvite() method. 
     * @return Event sink used to notify caller on invalid invite code. 
     */
    public: virtual GEventSink decodeInvite(const GString& code, int32 mode, const GInvite& invite) = 0;
    
    /**
     * The method is provided for convenience. For the most part it is intended to extract
     * Glymose invite codes from free form messages containing Glympse URLs. 
     * Once invite code is extracted, further processing is delegated to IGlympse::decodeInvite. 
     *
     * It is highly recommended to use this method instead of parsing Glympse URLs manually.
     * Glympse URL format can be changed in future. The API is always aware of all supported formats
     * and variations.
     *
     * The method is useful for applications doing their own SMS, Email scraping or
     * providing custom transport mechanism for invites delivery.
     * 
     * Here are some examples of messages handled by this method:
     * - "Click for a Glympse of my location: http://glympse.com/bot-002"
     * - "Here is where I am http://glympse.com/bot-002 See you there!"
     * - "http://glympse.com/bot-002"
     *
     * @param message Message text containing Glympse URI.
     * @param mode Bitmask used to configure method behaviour (see GC::INVITE_MODE_* for more details). 
     * @param invite Optional argument that identifies source (person) of the message.
     * @return true, if message is not empty.
     */
    public: virtual bool openUrl(const GString& message, int32 mode, const GInvite& invite) = 0;
    
    /**
     * Parses the message looking for Glympse URIs and extracts invite codes. 
     *
     * Invite codes returned by this method are formatted in the way Client API stores them internally.
     * Dashes and other allowed punctuation are removed.
     *
     * The method is thread-safe. It can be called from any application thread.
     * @note It is absolutely required to pass all invites to main thread for decoding.
     *
     * @param message Message text containing Glympse URI.
     * See openUrl() for more details on message format.
     * @return The list of invite codes extracted from the message or NULL if no invite codes were found.
     */
    public: virtual GArray<GString>::ptr extractInviteCodes(const GString& message) = 0;
    
    /**
     * Determines invite aspect (type of object hidden behind the invite code).
     * See GC#INVITE_ASPECT_* for the list of supported aspects.
     *
     * There are some cases, when invite aspect cannot be determined locally.
     * Server round trip might be required to disambiguate.
     *
     * The method is thread-safe. It can be called from any application thread.
     * @note It is absolutely required to pass all invites to main thread for decoding.
     *
     * @note The feature is only supported since API build in 2.0.40.
     * Prior to 2.0.40 the method always returns GC#INVITE_ASPECT_UNDETERMINED.
     * 
     * @param code Invite code to be analyzed. 
     * @return Detected invite aspect. See GC#INVITE_ASPECT_* for more details.
     */
    public: virtual int32 getInviteAspect(const GString& code) = 0;
    
    /**
     * Creates snapshot image of a ticket invite.
     *
     * The method returns immediately. Returned image object can be used to subscribe on events and
     * be notified, when snapshot image is ready (generated and downloaded from server).
     *
     * It might take up to a few minutes to generate a snapshot, which in turn always happens on server side.
     * Platform will not reissue any requests during next session, if being stopped while loading is in process.
     *
     * Invite snapshots can only be created, when platform is started and is authenticated
     * (GE::PLATFORM_LOGIN_SUCCEEDED has already been received during this session).
     *
     * @param invite Ticket invite code (e.g. "XXX-XXX").
     * @param parameters Set of required parameters of target image.
     * - width: image width in pixels.
     * - height: image height in pixels.
     * @param style Optional styling profile to be applied to the snapshot.
     * @return Image object or NULL, if invite snapshot cannot be created at the moment.
     */
    public: virtual GImage createInviteSnapshot(const GString& invite, const GPrimitive& parameters, const GPrimitive& style) = 0;        
    
    /**
     * @name Tickets Section
     *
     * Basic tools for operating with incoming and outgoing tickets and requests.
     */
    
    /**
     * This method should be used to continue watching ticket, which has already been decoded
     * via decodeInvite() method. Object implementing IUserTicket interface is sent along with
     * GE::PLATFORM_INVITE_TICKET event to platform subscribers. 
     *
     * @param userTicket Object, which was sent along with GE::PLATFORM_INVITE_TICKET event 
     * to platform subscribers.
     * @return The method returns reference to ticket object. 
     * NULL value is returned any of the following cases:
     * - IUserTicket object is malformed;
     * - Ticket with such code is already registered on the system;
     * - Ticket is sent by the same application instance (associated user is self user).
     */
    public: virtual GTicket viewTicket(const GUserTicket& userTicket) = 0;
    
    /**
     * Creates and sends a Glympse.
     *
     * You must first create a ticket object via GlympseFactory#createTicket with at least one recipient, 
     * optional duration, optional message, and optional destination.
     * The sendTicket() will create the Glympse, and send a unique Glympse code to each of the recipients.
     * 
     * The ticket you pass to this method will be added to the IHistoryManager,
     * which can be obtained by calling the getHistoryManager method.
     *
     * The method always returns synchronously. Ticket creation as well as invite delivery 
     * is performed in the background. See GE#LISTENER_TICKET events for more details.
     *
     * Platform will keep trying to send a ticket forever until it gets a chance to reach Glympse servers. 
     * It may take a while under poor data reception conditions. There is a way to limit amount of time 
     * during which platform performs retries. See IHistoryManager#enableCancellationTimer() and
     * IHistoryManager#setCancellationTimeout() for more details.
     *
     * @return true if ticket creation has been scheduled.
     */
    public: virtual bool sendTicket(const GTicket& ticket) = 0;
    
    /**
     * Creates and sends Glympse request. 
     * You must first create a ticket object via GlympseFactory#createTicket with one Invite. The invite should
     * have an attached request ticket with optional duration, optional message, and optional destination. The
     * attached request ticket should also contain at least one Invite descibing how the requested ticket should
     * be delivered.
     *
     * Request recipient will receive regular Glympse link and will be able to send a Glympse 
     * by opening the link in the Glympse application.
     * 
     * @param ticket Ticket object with default parameters prepopulated (duration, message, destination).  
     * Ticket object must contain single recipient identifying current user. 
     * @ return true if the input ticket was validated and scheduled.
     */
    public: virtual void requestTicket(const GTicket& ticket) = 0;
    
    /**
     * @name Helpers
     *
     * Miscellaneous helper utilities. 
     */
    
    /**
     * This method verifies the Glympse environment as it is currently configured and throws an exception
     * if errors are encountered. The verification is dependent both on the configuration as it exists at
     * the time the method is invoked, as well as the os environment on which the environment is running.
     *
     * It is recommended that method is invoked after configuring the Glympse platform instance, but before
     * starting it. Note also that this method is provided solely for convenience and neend't be called 
     * every time the platform is started. However, it is prudent to test it periodically and/or before
     * shipping your Glympse-enabled application.
     *
     * @throws GlympseException under varying invalid conditions.
     */
    public: virtual void verify() = 0;

    /**
     * Gets the epoch time (milliseconds since 1/1/1970) of the corrected system time ("Glympse time").
     * All timestamps used throughout the Glympse system are server timestamps in UTC. These include ticket start and end times.
     * The Glympse client API periodically synchronizes itself to the Glympse server time in order to maintain an accurate
     * system time that is independent to the system time maintained by the operating system, which may be incorrect.
     * Any time you need an accurate system time to use with other Glympse times (such as when computing time remaining on a ticket),
     * you should call this method to obtain the current system time in UTC.
     *
     * @return The current system time, corrected to be in sync with the Glympse server time.
     */
    public: virtual int64 getTime() = 0;
    
    /**
     * Gets version of the library in the format: "{MAJOR}.{MINOR}.{BUILD}".
     *
     * MAJOR is major SDK version.
     * MINOR is minor SDK version.
     * BUILD is forever increasing SDK version number.
     *
     * Example: "2.0.41"
     */
    public: virtual GString getApiVersion() = 0;
    
    /**
     * Gets version of the library in the format: "{MAJOR}.{MINOR}.{BUILD}.{BUGFIX} {STATUS}.{ITER}".
     *
     * BUGFIX is optional SDK bug fix iteration number.
     * STATUS is optional development status (in-progress, beta, release, etc.).
     * ITER is optional sprint number within STATUS phase.
     *
     * Examples:
     * - "2.0.40 Dev.2"
     * - "2.0.41 Beta"
     * - "2.0.41.1 Alpha"
     * - "2.0.41.2 Release"
     * - "2.1.42"
     */
    public: virtual GString getApiVersionFull() = 0;
    
    /**
     * @name Debug Tools
     *
     * These tools are provided for debugging purposes only and should never be invoked from
     * production code.
     */
    
    /**
     * This method presents object model explorer on top of application UI. 
     */
    public: virtual void showDebugView() = 0;
    
    /**
     * Glympse API supports few levels of log detalization. Levels are controlled 
     * by Glympse server, which allows to enable detailed logging for specific 
     * user to troubleshoot an issue. By default only critial errors are logged and
     * uploaded to Glympse server for further analysis.
     *
     * This method could be used by application to override logging levels for
     * current Glympse API instance.
     * 
     * See CoreConstants for the list of supported levels.
     *
     * @param fileLevel Level of details for logging to file.
     * @param debugLevel Level of details for logging to console.
     */
    public: virtual void overrideLoggingLevels(int32 fileLevel, int32 debugLevel) = 0;
    
    /**
     * Returns full name and path to the log file which is currently in use.
     * File name changes every time when API starts.
     * File path usually remains the same during entire application session.
     */
    public: virtual GString getLogFile() = 0;
    
    /**
     * Returns the list of all sinks to which specified listener is subscribed.
     */
    public: virtual GArray<GEventSink>::ptr findSinks(const GEventListener& listener) = 0;
    
    /**
     * @name PUSH Tools
     */

    /**
     * Associates device PUSH handle with Glympse user account. 
     *
     * @param deviceToken Push handle provided by device.
     */
    public: virtual void registerDeviceToken(const GString& deviceToken) = 0;
    
    /**
     * Associates device PUSH handle with a given device.
     *
     * @param provider Push provider type.
     * @param deviceToken Push handle provided by device.
     */
    public: virtual void registerDeviceToken(const GString& tokenType, const GString& deviceToken) = 0;
    
    /**
     * Clears PUSH handle associated with Glympse user account.
     */
    public: virtual void unregisterDeviceToken() = 0;
    
    /**
     * Clears PUSH handle associated with a given device.
     */
    public: virtual void unregisterDeviceToken(const GString& tokenType) = 0;
    
    /**
     * Checks to see if platform still has valid device token. 
     * Host application needs to initiate PUSH registration and obtain new token from
     * PUSH provider otherwise.
     */
    public: virtual bool hasValidDeviceToken() = 0;
    
    /**
     * Checks to see if platform still has valid device token. 
     * Host application needs to initiate PUSH registration and obtain new token from
     * PUSH provider otherwise.
     */
    public: virtual bool hasValidDeviceToken(const GString& tokenType) = 0;
    
    /**
     * Sends PUSH notification "payload" to Client API for processing.
     *
     * @param payload PUSH notification payload.
     */
    public: virtual void handleRemoteNotification(const GString& payload) = 0;
    
    /**
     * Sends PUSH notification "payload" to Client API for processing.
     *
     * @param payload PUSH notification payload.
     * @param context Arbitrary context to be associated with further callbacks.
     */
    public: virtual void handleRemoteNotification(const GString& payload, const GString& context) = 0;
    
    /**
     * Glympse server sends "echo" PUSH message to the device every time when ticket gets created.
     * Device is supposed to confirm that the message is received. The technique is used to verify
     * whether device is capable of receiving notifications over PUSH. In some cases it is critical 
     * for server to know that PUSH mechanism is reliable enough to make product level decisions
     * based on its availability. Specifically speaking server can set relatively low post rate
     * (long interval between locaiton uploads) for the scenario when no one is viewing any of active
     * tickets originated from the device.
     *
     * Some applications might want to disable going into this "idle" mode even when no one is viewing. 
     * This method allows to toggle echoing logic to achieve desired behavior.
     *
     * The method can be called at any time, but the change will only make affect upon sending the next ticket.
     * It is recommended to call it before platform is started and do not toggle for the lifetime of the platform.
     * The preference is not persisted by Glympse API.
     *
     * Echoing is enabled by default.
     *
     * @param enable Flag indicating whether echoing needs to be enabled.
     */
    public: virtual void enablePushEchoing(bool enable) = 0;
    
    /**
     * Tells whether PUSH echoing is currently enabled.
     */
    public: virtual bool isPushEchoingEbabled() = 0;
};
    
/*C*/typedef O< IGlympse > GGlympse;/**/
    
}

#endif // !IGLYMPSE_H__GLYMPSE__
