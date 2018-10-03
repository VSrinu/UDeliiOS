//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef GLYMPSEEVENTS_H__GLYMPSE__
#define GLYMPSEEVENTS_H__GLYMPSE__

namespace Glympse 
{
    
/**
 * Declares the list of event broadcasters and all supported events. 
 */
/*O*public**/ class GlympseEvents
{
    /**
     * @name Listener types
     * The list of all event broadcasters on the system.
     */
    
    /**
     * Platform events. 
     * Use IGlympse event sink to subscribe on these events.
     */    
    public: static const int32 LISTENER_PLATFORM                = 1;
    
    /**
     * Invite related events. 
     */    
    public: static const int32 LISTENER_INVITE                  = 2;
    
    /**
     * User events.
     * Use IUser event sink to subscribe on these events.
     */        
    public: static const int32 LISTENER_USER                    = 3;
    
    /**
     * Ticket events.
     * Use ITicket event sink to subscribe on these events.
     */        
    public: static const int32 LISTENER_TICKET                  = 4;
    
    /**
     * Network manager events.
     * Use INetworkManager event sink to subscribe on these events.
     */        
    public: static const int32 LISTENER_NETWORK                 = 5;     
    
    /**
     * Battary manager events.
     * Use IBatteryManager event sink to subscribe on these events.
     */        
    public: static const int32 LISTENER_BATTERY                 = 6;         
    
    /**
     * Image events.
     * Use IImage event sink to subscribe on these events.
     */        
    public: static const int32 LISTENER_IMAGE                   = 7;          
    
    /**
     * Location manager events.
     * Use ILocationManager event sink to subscribe on these events.
     */        
    public: static const int32 LISTENER_LOCATION                = 8;
    
    /**
     * Group manager events.
     * Use IGroupManager event sink to subscribe on these events.
     */    
    public: static const int32 LISTENER_GROUPS                  = 9;
    
    /**
     * Group events.
     * Use IGroup event sink to subscribe on these events.
     */
    public: static const int32 LISTENER_GROUP                   = 10;
    
    /**
     * Config events.
     * Use IConfig event sink to subscribe on these events.
     */
    public: static const int32 LISTENER_CONFIG                  = 11;
    
    /**
     * Handoff events.
     * Use IHandoffManager event sink to subscribe on these events.
     */
    public: static const int32 LISTENER_HANDOFF                 = 12;
    
    /**
     * Linked account events.
     * Use ILinkedAccountsManager event sink to subscribe on these events.
     */
    public: static const int32 LISTENER_LINKED_ACCOUNTS         = 13;
    
    /**
     * Applications manager events.
     * Use IApplicationsManager event sink to subscribe on these events.
     */
    public: static const int32 LISTENER_APPLICATIONS            = 14;
    
    /**
     * Triggers manager events.
     * Use ITriggersManager event sink to subscribe on these events.
     */
    public: static const int32 LISTENER_TRIGGERS                = 15;
    
    /**
     * Place search events.
     * Use IPlaceSearchEngine event sink to subscribe on these events.
     */
    public: static const int32 LISTENER_PLACE_SEARCH            = 16;

    /**
     * Pairing events.
     * Use IPairingManager event sink to subscribe to these events.
     */
    public: static const int32 LISTENER_PAIRING                 = 17;

    /**
     * Favorites events.
     * Use IFavoritesManager event sink to subscribe to these events.
     */
    public: static const int32 LISTENER_FAVORITES               = 18;

    /**
     * Directions events.
     * Use IDirections event sink to subscribe to these events.
     */
    public: static const int32 LISTENER_DIRECTIONS              = 19;
    
    /**
     * Confirnation code events.
     * Events are fired when application is requesting cinfirmation code to be sent out.
     */
    public: static const int32 LISTENER_CONFIRMATION_CODE       = 20;

    /**
     * CardManager events.
     * Use ICardManager event sink to subscribe to these events.
     */
    public: static const int32 LISTENER_CARDS                   = 21;

    /**
     * CardManager events.
     * Use ICard event sink to subscribe to these events.
     */
    public: static const int32 LISTENER_CARD                    = 22;

    /**
     * CardActivity events.
     * Use ICardActivity event sink to subscribe to these events.
     */
    public: static const int32 LISTENER_CARD_ACTIVITY           = 23;

    /**
     * CardMember events.
     * Use ICardMember event sink to subscribe to these events.
     */
    public: static const int32 LISTENER_CARD_MEMBER             = 24;

    /**
     * CardInvite events.
     * Use ICardInvite event sink to subscribe to these events.
     */
    public: static const int32 LISTENER_CARD_INVITE             = 25;
    
    /**
     * PoiManager events.
     * Use IPoiManager event sink to subscribe to these events.
     */
    public: static const int32 LISTENER_POIS                    = 26;
    
    /**
     * Invite viewers events.
     * Use IInviteViewers event sink to subscribe to these events.
     */
    public: static const int32 LISTENER_INVITE_VIEWERS          = 30;
    
    /**
     * @name Platform events. 
     *
     * Events broadcasted by LISTENER_PLATFORM.
     */
    
    /**
     * This event is broadcast when the platform creates a new account on the server.
     * Once created, accounts are persisted until either the application is uninstalled
     * or until GGlympse::logout() is explicitly invoked.
     */
    public: static const int32 PLATFORM_ACCOUNT_CREATED         = 0x00000002;

    /**
     * This event is broadcast when no local account exists, but the platform fails to 
     * create a new account on the server. This error is fatal and the platform will
     * be stopped automatically and cannot be restarted.
     */
    public: static const int32 PLATFORM_ACCOUNT_CREATE_FAILED   = 0x00000004;
    
    /**
     * This event is broadcast every time local account credentials are successfully
     * exchanged for a valid access token or when a valid access token is successfully
     * extracted from the local cache.
     */
    public: static const int32 PLATFORM_LOGIN_SUCCEEDED         = 0x00000008;
    
    /**
     * This event is broadcast when local account credentials are unable to be exchanged
     * for a valid access token, but for an unknown reason. This error is fatal and the
     * platform will be stopped automatically and cannot be restarted.
     */
    public: static const int32 PLATFORM_LOGIN_FAILED            = 0x00000020;

    /**
     * This event is broadcast when a network connection fails due to an expired access
     * token. The platform will automatically re-attempt authentication to retrieve a
     * new, valid access token.
     */
    public: static const int32 PLATFORM_SESSION_FAILED          = 0x00000040;
    
    public: static const int32 PLATFORM_SYNCED_WITH_SERVER      = 0x00000080;
    public: static const int32 PLATFORM_STARTED                 = 0x00000100;
    public: static const int32 PLATFORM_STOPPED                 = 0x00000200;
    public: static const int32 PLATFORM_LOCATION                = 0x00000400;
    public: static const int32 PLATFORM_LOCATIONS_APPENDED      = 0x00000800;
    public: static const int32 PLATFORM_DATA_APPENDED           = 0x00001000;
    public: static const int32 PLATFORM_USER_ADDED              = 0x00002000;
    public: static const int32 PLATFORM_USER_REMOVED            = 0x00004000;
    public: static const int32 PLATFORM_USER_CHANGED            = 0x00008000;
    public: static const int32 PLATFORM_USER_LIST_REORDERED     = 0x00010000;
    public: static const int32 PLATFORM_TICKET_ADDED            = 0x00020000;
    public: static const int32 PLATFORM_TICKET_REMOVED          = 0x00040000;
    public: static const int32 PLATFORM_TICKET_CHANGED          = 0x00080000;
    public: static const int32 PLATFORM_TICKET_LIST_REORDERED   = 0x00100000;
    public: static const int32 PLATFORM_TICKET_ARRIVED          = 0x00200000;
    public: static const int32 PLATFORM_INVITE_TICKET           = 0x00400000;
    public: static const int32 PLATFORM_INVITE_REQUEST          = 0x00800000;

    /**
     * This event is broadcast when the platform is started if, and only if, this is
     * the FIRST time that the platform has been started. Note that due to the criteria
     * used to detect this condition, all calls to IGlympse::logout() will cause this
     * event to be fired the next time that a platform instance is started.
     */
    public: static const int32 PLATFORM_FIRST_LAUNCH            = 0x01000000;
    
    /**
     * This event is fired, when server rate limits access to API for certain device or API key.
     *
     * Sandbox is the only environment, which is rate limited. The following rules are applied, 
     * when developing against sandbox:
     * - Maximum of 30 requests per 60 seconds are allowed per device;
     * - Maximum of 20 devices are allowed per API key.
     *
     * API does not handle this case in any way other than spreading the event.
     * Requests that are rate limited are not retried.
     */
    public: static const int32 PLATFORM_RATE_LIMITED            = 0x02000000;
    
    /**
     * The event is fired when platform state changes between forground and background.
     * Application alters platform state through IGlympse#setActive() method.
     */
    public: static const int32 PLATFORM_STATE_CHANGED           = 0x04000000;
    
    /**
     * The event is fired if invite to join a card is decoded.
     *
     * @param An object of GCard type in GC#CARD_STATE_PREVIEW state.
     */
    public: static const int32 PLATFORM_CARD_INVITE             = 0x10000000;
    
    /**
     * The event is fired if request to join a card is decoded.
     *
     * @param An object of GCardInvite type.
     */
    public: static const int32 PLATFORM_CARD_REQUEST            = 0x20000000;
    
    public: static const int32 PLATFORM_USER_LIST_CHANGED            
        = PLATFORM_USER_ADDED
        | PLATFORM_USER_REMOVED
        | PLATFORM_USER_LIST_REORDERED
        | PLATFORM_LOCATION
        | PLATFORM_USER_CHANGED;
    public: static const int32 PLATFORM_TICKET_LIST_CHANGED            
        = PLATFORM_TICKET_ADDED
        | PLATFORM_TICKET_REMOVED
        | PLATFORM_TICKET_LIST_REORDERED
        | PLATFORM_TICKET_CHANGED
        | PLATFORM_TICKET_ARRIVED;
    
    /**
     * @name Invite events.     
     *
     * Events broadcasted by LISTENER_INVITE.
     */

    /**
     * The event is fired, when specified invite code is decoded successfully.
     * @param code Invite code of IString type.
     */
    public: static const int32 INVITE_DECODED                   = 0x00000001;
    
    /**
     * The event is fired, when specified invite code occurs to be invalid.
     * @param code Invite code of IString type.
     */ 
    public: static const int32 INVITE_INVALID_CODE              = 0x00000002;
    
    /**
     * @name User events.     
     *
     * Events broadcasted by LISTENER_USER.
     */
    
    /**
     * User nickname has been changed.
     *
     * @param account Object of IUser type.
     */
    public: static const int32 USER_NICKNAME_CHANGED            = 0x00000001;
    
    /**
     * User's "most important" ticket has been changed.
     *
     * @param account Object of IUser type.
     */
    public: static const int32 USER_ACTIVE_TICKET_CHANGED       = 0x00000002;
    
    /**
     * New ticket has been added under the user.
     *
     * @param account Object of ITicket type.
     */
    public: static const int32 USER_TICKET_ADDED                = 0x00000004;
    
    /**
     * One of user's tickets has been removed.
     *
     * @param account Object of ITicket type.
     */
    public: static const int32 USER_TICKET_REMOVED              = 0x00000008;
    
    /**
     * Avatar upload operation completed successully.
     *
     * @param account Object of IUser type.
     */
    public: static const int32 USER_AVATAR_UPLOADED             = 0x00000010;

    /**
     * Avatar was not uploaded for whatever reason (network failure, etc.).
     *
     * @param account Object of IUser type.
     */
    public: static const int32 USER_AVATAR_NOT_UPLOADED         = 0x00000020;
    
    /**
     * The user's "most important" ticket is about to change. This is only fired
     * if the user currently has an active ticket.
     *
     * @param account Object of IUser type.
     */
    public: static const int32 USER_ACTIVE_TICKET_RESIGNING     = 0x00000040;

    /**
     * A combination of flags indicating that something has changed about the user.
     */
    public: static const int32 USER_CHANGED                     
        = USER_NICKNAME_CHANGED
        | USER_ACTIVE_TICKET_CHANGED
        | USER_TICKET_ADDED
        | USER_TICKET_REMOVED
        | USER_AVATAR_UPLOADED;

    /**
     * @name Ticket events. 
     *
     * Events in this section are fired, when any ticket properties are changed.
     *
     * You should not expect any events to be fired by expired or sibling tickets.
     * Even though objects itself can be modified under the covers, API does not provide 
     * mechanisms for notifying host application on changes. It is still possible to pull 
     * and visualize updates periodically. 
     *
     * The only exception from the rule above is TICKET_TRANSFERRED event.
     * 
     * Events broadcasted by LISTENER_TICKET.
     */
    
    /**
     * The event indicates that outgoing ticket has been successfully created. 
     *
     * At this point initial ticket properties (message, destination) are not associated
     * with ticket object on server and ticket invites are not sent yet. Even invite codes
     * are not assigned yet.
     */
    public: static const int32 TICKET_CREATED                   = 0x00000001;
    
    /**
     * The event is sent, when ticket expires. 
     * 
     * This may or may not happen right away depending on some external factors that are 
     * out of control for the API. Network connectivity issues may delay 
     */
    public: static const int32 TICKET_EXPIRED                   = 0x00000002;
    
    /**
     * The event is fired, when ticket is added for viewing.
     */
    public: static const int32 TICKET_FIRST_VIEWED              = 0x00000004;        
    public: static const int32 TICKET_VISIBILITY_CHANGED        = 0x00000008;
    public: static const int32 TICKET_DURATION_CHANGED          = 0x00000010;
    public: static const int32 TICKET_MESSAGE_CHANGED           = 0x00000020;    
    public: static const int32 TICKET_DESTINATION_CHANGED       = 0x00000040;    
    public: static const int32 TICKET_TRACK_CHANGED             = 0x00000080;
    public: static const int32 TICKET_ETA_CHANGED               = 0x00000100;    
    public: static const int32 TICKET_ROUTE_CHANGED             = 0x00000200;
    public: static const int32 TICKET_TRAVEL_MODE_CHANGED       = 0x00000400;
    public: static const int32 TICKET_INVALID_CODE              = 0x00000800;
    public: static const int32 TICKET_INVITE_CREATED            = 0x00001000;
    public: static const int32 TICKET_INVITE_SENT               = 0x00002000;
    
    /**
     * This event is fired periodically while any invites of the ticket are being watched.
     * The event is also fired at least once, when ticket is no longer watched. 
     *
     * @see ITicket#isSomeoneWatching()
     * @param Object of Ticket type.
     */
    public: static const int32 TICKET_INVITE_UPDATED            = 0x00004000;
    
    public: static const int32 TICKET_INVITE_REMOVED            = 0x00008000;     
    public: static const int32 TICKET_INVITE_FAILED             = 0x00010000;           
    public: static const int32 TICKET_REQUEST_CREATED           = 0x00020000;                       
    public: static const int32 TICKET_REQUEST_SENT              = 0x00040000; 
    public: static const int32 TICKET_REQUEST_FAILED            = 0x00080000;           
    public: static const int32 TICKET_FAILED                    = 0x00100000;
    
    /**
     * TICKET_ARRIVED event is fired when sender of ticket has arrived at destination     
     */
    public: static const int32 TICKET_ARRIVED                   = 0x00200000;          
    
    /**
     * This event is sent, when any properties are appended to the ticket.
     * This is event is sent per ticket.
     * 
     * @param data Object of IDataEvent type.      
     */
    public: static const int32 TICKET_DATA_APPENDED             = 0x00400000;
    
    /**
     * This event is sent, when any properties are cleared on the ticket.
     * This is event is sent per ticket.
     *
     * @param data Object of IDataEvent type.
     */
    public: static const int32 TICKET_DATA_CLEARED              = 0x00800000;
    
    /**
     * This event is fired, when ticket ownership changes.
     *
     * @see ITicket#isMine()
     * @param data Object of ITicket type.
     */
    public: static const int32 TICKET_TRANSFERRED               = 0x01000000;
    
    /**
     * This event is fired, when ticket ownership is not transferred for some reason.
     *
     * @param data Object of ITicket type.
     */
    public: static const int32 TICKET_NOT_TRANSFERRED           = 0x02000000;
    
    /**
     * This event is sent, when ticket is considered to become immutable
     * (meaning none of ticket properties can change since after this point).
     *
     * @param data Object of ITicket type.
     */
    public: static const int32 TICKET_COMPLETED                 = 0x04000000;
    
    public: static const int32 TICKET_INVITE_CHANGED
        = TICKET_INVITE_CREATED
        | TICKET_INVITE_SENT
        | TICKET_INVITE_UPDATED    
        | TICKET_INVITE_REMOVED    
        | TICKET_INVITE_FAILED;
    public: static const int32 TICKET_CHANGED                   
        = TICKET_EXPIRED
        | TICKET_DURATION_CHANGED
        | TICKET_MESSAGE_CHANGED
        | TICKET_DESTINATION_CHANGED
        | TICKET_TRACK_CHANGED
        | TICKET_ETA_CHANGED
        | TICKET_ROUTE_CHANGED
        | TICKET_TRAVEL_MODE_CHANGED
        | TICKET_INVITE_CHANGED
        | TICKET_VISIBILITY_CHANGED
        | TICKET_FAILED
        | TICKET_ARRIVED
        | TICKET_TRANSFERRED
        | TICKET_COMPLETED;
    
    /**
     * @name Network events.     
     *
     * Events broadcasted by LISTENER_NETWORK.
     */

    /**
     * This notification is spread right after the first network failure.
     * The message is not sent upin subsequent failures.
     */
    public: static const int32 NETWORK_START_FAILING                = 0x00000001;
    
    /**
     * The message is sent, when the first network request succeeds after any failures.
     */
    public: static const int32 NETWORK_RECOVERED                    = 0x00000002;
    
    /**
     * This notification is sent, when Network Manager schedules next request.
     *
     * @param delay Object of ILong type.
     */
    public: static const int32 NETWORK_WILL_SEND_REQUEST            = 0x00000010;
    
    /**
     * The event is fired in process of preparing network post to let others
     * contribute to it.
     *
     * It is followed by GE#NETWORK_IS_SENDING_REQUEST if platform collects enough 
     * info to make the post.
     */
    public: static const int32 NETWORK_IS_PREPARING_REQUEST         = 0x00000020;
    
    /**
     * The event is sent every time, when Client API does final preparations before
     * issueing next network request. Event handlers still have a chance to append 
     * commands to the batch, that API is preparing to issue. 
     *
     * See Programming Guide for more details. 
     */
    public: static const int32 NETWORK_IS_SENDING_REQUEST           = 0x00000040;
    
    /**
     * The event is fired upon every post rate calculation.
     */
    public: static const int32 NETWORK_POST_RATE_CALCULATED         = 0x00000080;
    
    /**
     * The event is fired when network manager is done executing request previously
     * scheduled via INetworkManager#issueHttpRequest().
     *
     * @param response Object of GPrimitive type.
     */
    public: static const int32 NETWORK_RESPONSE_RECEIVED            = 0x00000100;
    
    /**
     * The event is fired when time sync occurs after significant local time change.
     */
    public: static const int32 NETWORK_CLOCKS_SYNCED                = 0x00000200;
    
    /**
     * The event is fired when the availability of push notifications has changed.
     */
    public: static const int32 NETWORK_PUSH_AVAILABILITY_CHANGED    = 0x00000400;
    
    /**
     * @name BATTERY events.     
     *
     * Events broadcasted by LISTENER_BATTERY.
     */
    public: static const int32 BATTERY_STATE_CHANGED            = 0x00000001;

    /**
     * @name LOCATION events.     
     *
     * Events broadcasted by LISTENER_LOCATION.
     */
    
    /**
     * The event is fired, when location manager state changes.
     * See "Customizing Location Provider" section in the Programming Guide
     * and CC::LOCATION_STATE_* constants for more details.
     */
    public: static const int32 LOCATION_STATE_CHANGED           = 0x00000001;
    
    /**
     * The event is fired, when user enters one of currently monitored regions.
     */
    public: static const int32 LOCATION_REGION_ENTERED          = 0x00000010;
    
    /**
     * The event is fired, when user leaves one of currently monitored regions.
     */
    public: static const int32 LOCATION_REGION_LEFT             = 0x00000020;
    
    /**
     * The event accompanies one of battery saving techniques provided by the library. 
     * See "Leveraging Location Profiles" section in the Programming Guide.
     */
    public: static const int32 LOCATION_PROFILE_CHANGED         = 0x00000100;
    
    /**
     * The event is spread, when underlying location provider is stopped.
     * It means that all outgoing tickets have expired and location updates are lo longer required.
     */
    public: static const int32 LOCATION_PROVIDER_STOPPED        = 0x00000200;

    /**
     * @name IMAGE events.     
     *
     * Events broadcasted by LISTENER_IMAGE.
     */
    public: static const int32 IMAGE_CHANGED                    = 0x00000001;        

    /**
     * @name GROUPS (Manager) events.     
     *
     * Events broadcasted by LISTENER_GROUPS.
     */

    /**
     * Invite to start following public group was received and handled by the platform. 
     *
     * @param groupInvite Object of GGroupInvite type.
     */
    public: static const int32 GROUPS_INVITE                    = 0x00000001;
    
    /**
     * Private group was decoded successfully and is ready to be joined to.
     * The event is fired for each group separately. 
     *
     * @param group Object of GGroup type.     
     */    
    public: static const int32 GROUPS_DECODED                   = 0x00000002;    
    
    /**
     * New group was added to local list. 
     *
     * @param group Object of GGroup type.     
     */
    public: static const int32 GROUPS_GROUP_ADDED               = 0x00000004;        
    
    /**
     * Group was removed from local list. 
     *
     * @param group Object of GGroup type.     
     */    
    public: static const int32 GROUPS_GROUP_REMOVED             = 0x00000008;
    
    /**
     * Is fired once when platform finishes syncing the list of groups with server.
     */
    public: static const int32 GROUPS_SYNCED_WITH_SERVER        = 0x00000020;       
    
    /**
     * @name GROUP events.     
     *
     * Events broadcasted by LISTENER_GROUP.
     */

    /**
     * Invalid group code was specified.
     *
     * @param group Object of IGroup type.     
     */
    public: static const int32 GROUP_INVALID_CODE               = 0x00000001;      
    
    /**
     * One of group invites was created on server and is ready to be sent. 
     * This event is fired only, if client is responsible for sending and invite.
     *
     * @param group Object of IGroup type.     
     */
    public: static const int32 GROUP_INVITE_CREATED             = 0x00000002;          
    
    /**
     * Group invite was created and sent to recipient. 
     *
     * @param group Object of IGroup type.        
     */
    public: static const int32 GROUP_INVITE_SENT                = 0x00000004;              
    
    /**
     * For some reason invite delivery has failed. 
     *
     * @param group Object of IGroup type.        
     */ 
    public: static const int32 GROUP_INVITE_FAILED              = 0x00000008;   
    
    /**
     * New group member was added. 
     * 
     * @param group Object of IGroup type.             
     * @param member Object of IGroupMember type.                  
     */
    public: static const int32 GROUP_MEMBER_ADDED               = 0x00000010;                  
    
    /**
     * Group member was removed. 
     * 
     * @param group Object of IGroup type.             
     * @param member Object of IGroupMember type.                  
     */    
    public: static const int32 GROUP_MEMBER_REMOVED             = 0x00000020;                  
    
    /**
     * The order of group member list was changed.
     *
     * @param group Object of IGroup type.
     */
    public: static const int32 GROUP_ORDER_CHANGED              = 0x00000040;
    
    /**
     * Group has been viewed for the first time. 
     * 
     * @param group Object of IGroup type.             
     * @param member Object of IGroupMember type.                  
     */    
    public: static const int32 GROUP_FIRST_VIEWED               = 0x00000100;
    
    /**
     * Group member is now sharing new ticket with a group.
     * 
     * @param group Object of IGroup type.             
     * @param member Object of IGroupMember type.                  
     */        
    public: static const int32 GROUP_MEMBER_TICKET_CHANGED      = 0x00000200;

    /**
     * Group member has stopped sharing the current ticket with the group.
     *
     * @param group Object of IGroup type.
     * @param member Object of IGroupMember type.
     */
    public: static const int32 GROUP_MEMBER_TICKET_RESIGNING    = 0x00000400;

    /**
     * Group related error has occurred. More details counld be obtained from
     * IGroup#getState(). 
     * 
     * @param group Object of IGroup type.        
     */    
    public: static const int32 GROUP_FAILED                     = 0x00040000;       
    
    /**
     * Indicates that Group name was changed. 
     * 
     * @param group Object of IGroup type.        
     */
    public: static const int32 GROUP_NAME_CHANGED               = 0x00080000;     
    
    /**
     * Indicates that group was created or successfully or user joined the group successfully.
     * 
     * @param group Object of IGroup type.        
     */
    public: static const int32 GROUP_CREATED                    = 0x00100000;
    
    /**
     * @name Config events.
     *
     * Events broadcasted by LISTENER_CONFIG.
     */
    
    public: static const int32 CONFIG_XOA_CHANGED               = 0x00000001;
    public: static const int32 CONFIG_LOCATION_SHARING_CHANGED  = 0x00000002;
    public: static const int32 CONFIG_TICKET_SENT_CHANGED       = 0x00000004;
    public: static const int32 CONFIG_ACCOUNTS_LINKED_CHANGED   = 0x00000008;
    
    public: static const int32 CONFIG_CHANGED
        = CONFIG_XOA_CHANGED
        | CONFIG_LOCATION_SHARING_CHANGED
        | CONFIG_TICKET_SENT_CHANGED
        | CONFIG_ACCOUNTS_LINKED_CHANGED;
    
    /**
     * @name Handoff events.
     *
     * Events broadcasted by LISTENER_HANDOFF.
     */
    
    /**
     * The event is fired when handoff provider is recognized by the platform. 
     * 
     * @param provider Object of IHandoffProvider type.
     * @see IHandoffManager#getHandoffProvider
     */
    public: static const int32 HANDOFF_PROVIDER_CONNECTED       = 0x00000001;
    
    /**
     * The event is fired shortly after platform becomes active if handoff provider
     * is currently connected. 
     *
     * @param provider Object of IHandoffProvider type.
     * @see IHandoffProvider
     */
    public: static const int32 HANDOFF_PROVIDER_AVAILABLE       = 0x00000002;
    
    /**
     * The event is fired when handoff provider becomes unavailable.
     */
    public: static const int32 HANDOFF_PROVIDER_DISCONNECTED    = 0x00000004;

    /**
     * @name Custom Listener Identifiers
     *
     * Each class implementing IEventSink is associated with unique identifier,
     * which is passed to IEventListener#eventsOccurred() in listener argument.
     * This way event subscriber has a chance to demultiplex events coming from
     * various sources (broadcasters).
     *
     * Listener identifier is represented by 32-bit integer value.
     *
     * Host application is only allowed to allocate identifiers from the following interval
     * (LISTENER_ID_MIN, LISTENER_ID_MAX].
     */

    /**
     * Minimum value that can be used as custom listener identifier.
     */
    public: static const int32 LISTENER_ID_MIN                  = 0x7fff0000;

    /**
     * Maximum value that can be used as custom listener identifier.
     */
    public: static const int32 LISTENER_ID_MAX                  = 0x7fffffff;

    /**
     * @name Linked accounts events.
     *
     * Events broadcasted by LISTENER_LINKED_ACCOUNTS.
     */
    
    /**
     * The event is fired when an account is successfully linked with the user account.
     *
     * @param account Object of ILinkedAccount type.
     */
    public: static const int32 ACCOUNT_LINK_SUCCEEDED         = 0x00000001;

    /**
     * The event is fired when an account fails to link with the user account.
     *
     * @param account Object of ILinkedAccount type. Check getError() for error details.
     */
    public: static const int32 ACCOUNT_LINK_FAILED            = 0x00000002;

    /**
     * The event is fired when an account is successfully unlinked from the user account.
     *
     * @param account Object of ILinkedAccount type.
     */
    public: static const int32 ACCOUNT_UNLINK_SUCCEEDED       = 0x00000004;
    
    /**
     * The event is fired when an account fails to unlink from the user account.
     *
     * @param account Object of ILinkedAccount type. Check getError() for error details.
     */
    public: static const int32 ACCOUNT_UNLINK_FAILED          = 0x00000008;

    /**
     * The event is fired when an account is successfully refreshed in the user account.
     *
     * @param account Object of ILinkedAccount type.
     */
    public: static const int32 ACCOUNT_REFRESH_SUCCEEDED      = 0x00000010;
    
    /**
     * The event is fired when an account fails to refresh in the user account.
     *
     * @param account Object of ILinkedAccount type. Check getError() for error details.
     *
     * @note The object returned by getError() is only valid for the duration of the 
     * event handler. If it is necessary to retain the object beyond that lifetime, cache
     * a reference to the error object in the event handler.
     */
    public: static const int32 ACCOUNT_REFRESH_FAILED         = 0x00000020;

    /**
     * The event is fired when the list of linked accounts is successfully refreshed.
     *
     * @param NULL
     */
    public: static const int32 ACCOUNT_LIST_REFRESH_SUCCEEDED = 0x00000040;
    
    /**
     * The event is fired when the list of linked accounts fails to refresh.
     *
     * @param error Object of IServerError type.
     */
    public: static const int32 ACCOUNT_LIST_REFRESH_FAILED    = 0x00000080;
    
    /**
     * @name Confirmation code events.
     *
     * Events broadcasted by LISTENER_CONFIRMATION_CODE.
     */
    
    /**
     * The event is fired if confirmation code is successuffy generated and sent.
     *
     * @param account Object of GPrimitive type.
     */
    public: static const int32 CONFIRMATION_CODE_SENT         = 0x00000001;
    
    /**
     * The event is fired when server fails to generate or send confirmation code.
     *
     * @param account Object of IServerError type.
     */
    public: static const int32 CONFIRMATION_CODE_FAILED       = 0x00000002;
    
    /**
     * @name Applications manager events.
     *
     * Events broadcasted by LISTENER_APPLICATIONS.
     */
    
    /**
     * The event is fired when new application is added to the list.
     *
     * @param error Object of IApplication type.
     */
    public: static const int32 APPLICATIONS_APP_ADDED         = 0x00000001;

    /**
     * The event is fired when application is removed from the list.
     *
     * @param error Object of IApplication type.
     */
    public: static const int32 APPLICATIONS_APP_REMOVED       = 0x00000002;
    
    /**
     * The event is fired when application is removed from the list.
     *
     * @param error Object of IApplication type.
     */
    public: static const int32 APPLICATIONS_APP_CHANGED       = 0x00000004;
    
    /**
     * The event is fired when application is being lunched.
     *
     * @param error Object of IApplication type.
     */
    public: static const int32 APPLICATIONS_APP_LAUNCHED      = 0x00000008;
    
    /**
     * @name Triggers manager events.
     *
     * Events broadcasted by LISTENER_TRIGGERS.
     */
    
    /**
     * The event is fired when trigger is added.
     *
     * @param error Object of ITrigger type.
     */
    public: static const int32 TRIGGERS_TRIGGER_ADDED         = 0x00000001;
    
    /**
     * The event is fired when trigger is removed.
     *
     * @param error Object of ITrigger type.
     */
    public: static const int32 TRIGGERS_TRIGGER_REMOVED       = 0x00000002;
    
    /**
     * The event is fired when trigger is activated.
     *
     * @param error Object of ITrigger type.
     */
    public: static const int32 TRIGGERS_TRIGGER_ACTIVATED     = 0x00000004;

    /**
     * @name Pairing manager events.
     *
     * Events broadcasted by LISTENER_PAIRING.
     */

    /**
     * The event is fired after a pairing code was submittd and accepted.
     *
     * @param code Pairing code stored in GString.
     */
    public: static const int32 PAIRING_CODE_CLAIMED           = 0x00000001;

    /**
     * The event is fired after a pairing code was submitted but there was an error..
     *
     * @param ServerError with error details and code stored in the extra parameter.
     */
    public: static const int32 PAIRING_CODE_FAILED            = 0x00000002;

    /**
     * The event is fired after a request for pairing code was submittd and accepted.
     *
     * @param code Pairing code stored in GString.
     */
    public: static const int32 PAIRING_GET_CODE_SUCCEEDED     = 0x00000004;

    /**
     * The event is fired after a request for a pairing code was submitted but there was an error.
     *
     * @param ServerError with error details.
     */
    public: static const int32 PAIRING_GET_CODE_FAILED        = 0x00000008;

    /**
     * @name Place search events.
     *
     * Events broadcasted by LISTENER_PLACE_SEARCH.
     */
    
    /**
     * The event fires upon the completion of search request.
     *
     * @param error Object of IPlaceSearchResults type.
     */
    public: static const int32 PLACE_SEARCH_COMPLETED         = 0x00000001;
    
    /**
     * The event is fired if search request fails.
     *
     * @param error Object of IPlaceSearchRequest type.
     */
    public: static const int32 PLACE_SEARCH_FAILED            = 0x00000002;

    /**
     * @name Favorites manager events.
     *
     * Events broadcasted by LISTENER_FAVORITES.
     */

    /**
     * The event is fired if the list of favorites has changed.
     *
     * @param None.
     */
    public: static const int32 FAVORITES_CHANGED              = 0x00000001;

    /**
     * @name Directions events.
     *
     * Events broadcasted by LISTENER_DIRECTIONS.
     */

    /**
     * The event is fired if the directions have succeeded.
     *
     * @param None.
     */
    public: static const int32 DIRECTIONS_SUCCEEDED            = 0x00000001;

    /**
     * The event is fired if the directions have failed.
     *
     * @param None.
     */
    public: static const int32 DIRECTIONS_FAILED               = 0x00000002;

    /**
     * The event is fired if the directions have changed.
     *
     * @param None.
     */
    public: static const int32 DIRECTIONS_CHANGED
        = DIRECTIONS_SUCCEEDED
        | DIRECTIONS_FAILED;

    /**
     * @name CardManager manager events.
     *
     * Events broadcasted by LISTENER_CARDS.
     */

    /**
     * This event is sent when a card has been added.
     *
     * @param obj Object of ICard type.
     */
    public: static const int32 CARD_MANAGER_CARD_ADDED                 = 0x00000002;

    /**
     * This event is sent when a card has been removed.
     *
     * @param obj Object of ICard type.
     */
    public: static const int32 CARD_MANAGER_CARD_REMOVED               = 0x00000004;

    /**
     * This event is sent when the card manager has synced with the server after being started.
     *
     * @param None.
     */
    public: static const int32 CARD_MANAGER_SYNCED                     = 0x00000008;
    
    /**
     * This event is sent when the card manager fails to sync its state with the server.
     *
     * @param None.
     */
    public: static const int32 CARD_MANAGER_SYNC_FAILED                = 0x00000010;
    
    /**
     * This event is sent when the card types have been updated.
     *
     * @param None.
     */
    public: static const int32 CARD_MANAGER_CARD_TYPES_UPDATED         = 0x00000020;

    /**
     * @name Card events.
     *
     * Events broadcasted by LISTENER_CARD.
     */

    /**
     * This event is sent when a card state changes.
     *
     * @param obj Object of ICard type.
     */
    public: static const int32 CARD_STATE_CHANGED                     = 0x00000001;
    
    /**
     * This event is sent when a card name has been updated.
     *
     * @param obj Object of ICard type.
     */
    public: static const int32 CARD_NAME_UPDATED                      = 0x00000008;

    /**
     * This event is fired when member is added to the card.
     *
     * @param obj Object of ICardManager type.
     */
    public: static const int32 CARD_MEMBER_ADDED                      = 0x00000020;
    
    /**
     * This event is fired when member is removed from the card.
     *
     * @param obj Object of ICardManager type.
     */
    public: static const int32 CARD_MEMBER_REMOVED                    = 0x00000040;

    /**
     * This event is sent when a card invite has been added to a card.
     *
     * @param obj Object of ICardInvite type.
     */
    public: static const int32 CARD_INVITE_ADDED                      = 0x00000080;

    /**
     * This event is sent when a card invite has been removed.
     *
     * @param obj Object of ICardInvite type.
     */
    public: static const int32 CARD_INVITE_REMOVED                    = 0x00000100;
    
    /**
     * This event is fired when an object is added to the card.
     *
     * @param obj Object of ICardObject type.
     */
    public: static const int32 CARD_OBJECT_ADDED                      = 0x00000200;
    
    /**
     * This event is fired when an object is removed from the card.
     *
     * @param obj Object of ICardObject type.
     */
    public: static const int32 CARD_OBJECT_REMOVED                    = 0x00000400;
    
    /**
     * This event is fired when an object associated with this card is updated.
     *
     * @param obj Object of ICardObject type.
     */
    public: static const int32 CARD_OBJECT_UPDATED                    = 0x00000800;
    
    /**
     * This event is fired when an object failed to be removed from the card.
     *
     * @param obj Object of ICardObject type.
     */
    public: static const int32 CARD_OBJECT_REMOVAL_FAILED              = 0x00001000;
    
    /**
     * This event is sent when platform fails to delete a member.
     * In this case member remains on the list.
     *
     * @param obj Object of ICardMember type.
     */
    public: static const int32 CARD_MEMBER_DELETE_FAILED              = 0x00002000;
    
    /**
     * This event is fired when request to join a card fails to get accepted.
     * This can occur if request is revoked in between being received and accepted.
     *
     * @param obj Object of ICardInvite type.
     */
    public: static const int32 CARD_REQUEST_FAILED                    = 0x00004000;

    /**
     * @name CardActivity events.
     *
     * Events broadcasted by LISTENER_CARD_ACTIVITY.
     */

    /**
     * This event is sent when a card activity has changed.
     *
     * @param obj Object of ICardActivity type.
     */
    public: static const int32 CARD_ACTIVITY_CHANGED                  = 0x00000001;

    /**
     * This event is sent when a card activity has completed the initial sync with the server.
     *
     * @param obj Object of ICardActivity type.
     */
    public: static const int32 CARD_ACTIVITY_SYNCED                   = 0x00000002;
    
    /**
     * This event is sent when an event has been succesfully added to a card's activity
     *
     * @param obj Object of GCardEvent type
     */
    public: static const int32 CARD_EVENT_CREATED                     = 0x00000004;
    
    /**
     * This event is sent when an event fails to be created in a card's activity
     */
    public: static const int32 CARD_EVENT_CREATE_FAILED               = 0x00000008;

    /**
     * @name CardMember events.
     *
     * Events broadcasted by LISTENER_CARD_MEMBER.
     */

    /**
     * This event is sent when a card member started sharing.
     *
     * @param obj Object of ICardMember type.
     */
    public: static const int32 CARD_MEMBER_STARTED_SHARING            = 0x00000001;

    /**
     * This event is sent when a card member has stopped sharing.
     *
     * @param obj Object of ICardMember type.
     */
    public: static const int32 CARD_MEMBER_STOPPED_SHARING            = 0x00000002;
    
    /**
     * This event is sent when card member's ticket is initialized.
     *
     * @param obj Object of ICardMember type.
     */
    public: static const int32 CARD_MEMBER_TICKET_DECODED             = 0x00000004;

    /**
     * This event is sent when a card member has started a request.
     *
     * @param obj Object of ICardMember type.
     */
    public: static const int32 CARD_MEMBER_STARTED_REQUESTING         = 0x00000010;

    /**
     * This event is sent when a card member has stopped requesting.
     *
     * @param obj Object of ICardMember type.
     */
    public: static const int32 CARD_MEMBER_STOPPED_REQUESTING         = 0x00000020;
    
    /**
     * This event is sent when card member's request is initialized.
     *
     * @param obj Object of ICardMember type.
     */
    public: static const int32 CARD_MEMBER_REQUEST_DECODED            = 0x00000040;
    
    /**
     * This event is sent when card member declines someoneelse's request.
     * The event is only fired if declied request is still active at the time event is analyzed.
     *
     * @param obj Object of ICardMemberTicket type. 
     * ICardMemberTicket#getCardMember() points at card member declining a request.
     * ICardMemberTicket#getCardTicket() points at request being declined.
     */
    public: static const int32 CARD_MEMBER_REQUEST_DECLINED           = 0x00000080;

    /**
     * This event is sent when a card member state has changed.
     *
     * @param obj Object of ICardMember type.
     */
    public: static const int32 CARD_MEMBER_STATE_CHANGED              = 0x00000100;

    /**
     * @name CardInvite events.
     *
     * Events broadcasted by LISTENER_CARD_INVITE.
     */

    /**
     * This event is sent when a card invite has been created.
     *
     * @param obj Object of ICardInvite type.
     */
    public: static const int32 CARD_INVITE_CREATED                    = 0x00000001;

    /**
     * This event is sent when a card invite has been sent.
     *
     * @param obj Object of ICardInvite type.
     */
    public: static const int32 CARD_INVITE_SENT                       = 0x00000002;

    /**
     * This event is sent when a card invite send has failed.
     *
     * @param obj Object of ICardInvite type.
     */
    public: static const int32 CARD_INVITE_FAILED                     = 0x00000004;
    
    /**
     * @name POI events.
     *
     * Events broadcasted by LISTENER_POIS.
     */
    
    /**
     * The event is fired when the list of POIs has been synced with the server.
     */
    public: static const int32 POI_LIST_SYNCED                        = 0x00000001;
    
    /**
     * The event is fired when has been added to the list.
     *
     * @param poi Object of IPoi type.
     */
    public: static const int32 POI_ADDED                              = 0x00000002;
    
    /**
     * The event is fired when a POI has been updated.
     *
     * @param poi Object of IPoi type.
     */
    public: static const int32 POI_UPDATED                            = 0x00000004;
    
    /**
     * The event is fired when a POI has been removed from the list.
     *
     * @param poi Object of IPoi type.
     */
    public: static const int32 POI_REMOVED                            = 0x00000008;
    
    /**
     * @name Invite viewers events.
     *
     * Events broadcasted by LISTENER_INVITE_VIEWERS.
     */
    
    /**
     * The event is fired when new invite viewer is added.
     *
     * @param viewer Object of IInviteViewer type.
     */
    public: static const int32 INVITE_VIEWERS_ADDED                   = 0x00000001;
    
    /**
     * The event is fired when new invite viewer is removed.
     *
     * @param viewer Object of IInviteViewer type.
     */
    public: static const int32 INVITE_VIEWERS_REMOVED                 = 0x00000002;
    
    /**
     * The event is fired when the collection of invite viewers is cleared.
     *
     * @param None.
     */
    public: static const int32 INVITE_VIEWERS_CLEARED                 = 0x00000004;
};

}

#endif // !GLYMPSEEVENTS_H__GLYMPSE__
