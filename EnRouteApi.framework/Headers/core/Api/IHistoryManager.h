//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IHISTORYMANAGER_H__GLYMPSE__
#define IHISTORYMANAGER_H__GLYMPSE__

namespace Glympse 
{

/**
 * Contains a collection of outgoing (sent) Ticket objects ("Glympse history").
 * The sent ticket list contains all of the tickets you have created and sent.
 * This includes tickets that are still active as well as one that have expired.
 *
 * The list of outgoing tickets is always restored from server upon successful authentication
 * and is never cached locally to provide the most reliable and consisten behavior.
 *
 * @see ITicket
 */
/*O*public**/ struct IHistoryManager : public virtual ICommon
{
    /**
     * @name General
     *
     * Tools for accessing underlying collection of tickets.
     */
    
    /**
     * Determines whether local list has already been synced with server.
     * It might be useful to differenciate "empty history" case from "not yet synched" case.
     * Platform sends GE::PLATFORM_SYNCED_WITH_SERVER event, when this list is synced with server.
     *
     * @return Returns true, if local list has already been synced with server.
     */
    public: virtual bool isSynced() = 0;
    
    /**
     * Returns the sent ticket list collection ("Glympse history") as an array of ITicket objects.
     * 
     * The sent ticket list contains all the ticket you have created and sent.
     * This includes tickets that are still active as well as one that have expired.
     * 
     * This list will initially be empty. Once the Glympse API has communicated with the server,
     * the list will be populated to include the complete list of tickets you have sent.
     * 
     * To be notified when the list is first populated, you can register a IEventListener
     * and capture the GE::PLATFORM_SYNCED_WITH_SERVER event. 
     *
     * @return An array of sent tickets in the Glympse system.
     *
     * @see ITicket
     * @see IEventListener
     * @see GlympseEvents#PLATFORM_SYNCED_WITH_SERVER
     */
    public: virtual GArray<GTicket>::ptr getTickets() = 0;
    
    /**
     * Determines whether there are any active tickets on the list.
     *
     * @note Only visible tickets owned by this device are considered.
     *
     * @return true if there are any active, visible outgoing tickets owned by this device.
     */
    public: virtual bool anyActive() = 0;
    
    /**
     * Determines whether there are any active tickets on the list, optionally allowing
     * sibling tickets to be considered.
     * 
     * @note Only visible tickets are considered.
     *
     * @param siblings Indicates whether sibling tickets should be considered.
     * @return true if there are any active, visible outgoing tickets that match the sibling condition.
     */
    public: virtual bool anyActive(bool siblings) = 0;

    /**
     * Determines whether there are any active tickets on the list, optionally allowing
     * sibling tickets and hidden tickets to be considered.
     *
     * @param siblings Indicates whether sibling tickets should be considered.
     * @param visible Indicates whether tickets must be visible to be considered.
     * @return true if there are any active outgoing tickets that match the sibling and visibility conditions.
     */
    public: virtual bool anyActive(bool siblings, bool visible) = 0;

    /**
     * Forcibly pulls updates on last view time and view count for all outgoing
     * tickets (including expired). The method is mostly intended to refresh stats
     * of expired tickets. Client API pulls updates for active tickets automatically.
     * Client api will also prevent redundant requests to server, so it is not 
     * required to check for active tickets before making this call.
     */
    public: virtual void refresh() = 0;
    
    /**
     * This helper method walks through the colleciton of outgoing tickets and sends
     * GE#PLATFORM_TICKET_ADDED event to listener object for all active tickets found on the list.
     *
     * @note The method does nothing if events preceeding synchronization are enabled
     * (see enablePreSyncEvents() for details).
     *
     * @param listsner Event listener tht is to be notified on requested events.
     */
    public: virtual void simulateAddedEvents(const GEventListener& listener) = 0;
    
    /**
     * Determines whether invite can be sent by the platform instance. 
     * Platform checks invite type, host OS and installed 3rd party applications 
     * into account when preparing the result.
     *
     * The method does not perform any kind of address validation. It only checks
     * hypotetical possibility of sending the invite using any of client or server side 
     * delivery mechanisms.
     *
     * @param invite Invite object to be analyzed.
     * @return true if platform is capable of sending the invite.
     */
    public: virtual bool canSend(const GInvite& invite) = 0;
    
    /**
     * @name Configuration
     *
     * Tools for adjusting manager's behavior.
     */
    
    /**
     * Provides host application with an ability to minimize performance overhead
     * caused by numerous events fired during startup and initialization.
     *
     * The delivery of the following events is controlled by this method.
     * - GE#PLATFORM_TICKET_ADDED
     * - GE#PLATFORM_TICKET_REMOVED
     * - GE#PLATFORM_TICKET_CHANGED
     * - GE#PLATFORM_TICKET_LIST_REORDERED
     *
     * If this feature is disabled, none of the events above will be fired until
     * GE#PLATFORM_SYNCED_WITH_SERVER is fired.
     * 
     * Pre sync events are enabled by default. The method is supposed to be called
     * synchronously after platform startup in order to make affect.
     *
     * @param enable Tells whether pre sync events should be enabled or not.
     */
    public: virtual void enablePreSyncEvents(bool enable) = 0;

    /**
     * Checks if events can be fired before platform is fully synchronized with server.
     */
    public: virtual bool arePreSyncEventsEnabled() = 0;
    
    /**
     * Controls the behavior of automatic ticket cancellation. Ticket cancellation is a mechanism
     * that if enabled prevents platform from retrying ticket creation forever when device loses 
     * network connectivity.
     * 
     * Ticket cancellation is disabled by default.
     *
     * @param enable Pass true to enable the timer.
     */
    public: virtual void enableCancellationTimer(bool enable) = 0;

    /**
     * Determines whether ticket cancellation is enabled.
     *
     * @return true if ticket cancellation is enabled.
     */
    public: virtual bool isCancellationTimerEnabled() = 0;
    
    /**
     * Sets ticket cancellation timeout. Platform uses this value to determine when to stop ticket
     * creation attemps, if device is experiencing continuous network outage.
     *
     * @param timeout Amount of time in milliseconds during which platform will try to create a ticket.
     */
    public: virtual void setCancellationTimeout(int32 timeout) = 0;
    
    /**
     * Gets ticket cancellation timeout.
     *
     * @return Ticket cancellation timeout in milliseconds.
     */
    public: virtual int32 getCancellationTimeout() = 0;
    
    /**
     * Ticket expiration mode defines the way platform determines its state (sharing vs. not sharing).
     * Major differences between currently supported modes are focused on synchronizing platform
     * state with the server. Depending on applied mode platform can exclusively rely on properties 
     * which are synchronized with server (GC#EXPIRATION_MODE_SYNCHRONIZED - default) or
     * take into accounts local modifications that are not synchronized yet (GC#EXPIRATION_MODE_DETACHED).
     *
     * The method has to be called before platform completes original synchronization with server (see isSynced()).
     * 
     * @param mode Ticket expiration mode to be applied.
     */
    public: virtual void setExpirationMode(int32 mode) = 0;
    
    /**
     * Gets currently applied ticket expiration mode.
     *
     * @return The ticket expiration mode, which will be one of the GC#EXPIRATION_MODE constants.
     */
    public: virtual int32 getExpirationMode() = 0;
    
    /**
     * Sets callback listener to enable per-ticket control of XoA logic.
     *
     * @param listener An implementation of IXoAListener
     */
    public: virtual void setXoAListener(const GXoAListener& listener) = 0;
    
    /**
     * Triggers XoAManager to requery Ticket XoA status for each ticket it is listening to, through its IXoAListener.
     *
     * If no XoAListener has been set, this is call is ignored.
     */
    public: virtual void triggerXoAUpdate() = 0;

    /**
     * @name Properties
     *
     * Methods for accessing the most commonly used properties of the manager.
     */
    
    /**
     * Gets the time of when any of outgoing tickets was last viewed.
     * Invite creation is also considered as view.
     *
     * @return The most recent moment in the past, when one of tickets was viewed.
     */
    public: virtual int64 getLastViewTime() = 0;
        
    /**
     * @return Returns true, if any of active tickets is currently being watched.
     */
    public: virtual bool isSomeoneWatching() = 0;
    
    /**
     * @name Lookup Tools
     *
     * Set of convenience helpers for finding tickets.
     */
    
    /**
     * Gets the ITicket object that matches the given ticket ID.
     *
     * @param ticketId Ticket ID of the ticket you would like to find.
     * @return The ITicket object that matches the given ticket ID, 
     * or NULL if the ticket ID was not found.
     */
    public: virtual GTicket findTicketByTicketId(const GString& ticketId) = 0;
    
    /**
     * Gets the ITicket object that matches the given ticket invite code.
     *
     * @param code Invite code of the ticket you would like to find.
     * @return The ITicket object that matches the given invite code,
     * or NULL if the invite code was not found.
     */
    public: virtual GTicket findTicketByInviteCode(const GString& code) = 0;
};
    
/*C*/typedef O< IHistoryManager > GHistoryManager;/**/
    
}

#endif // !IHISTORYMANAGER_H__GLYMPSE__
