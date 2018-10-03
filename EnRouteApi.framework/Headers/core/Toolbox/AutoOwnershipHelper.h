//------------------------------------------------------------------------------
//
// Copyright (c) 2013 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef AUTOOWNERSHIPHELPER_H__TOOLBOX__GLYMPSE__
#define AUTOOWNERSHIPHELPER_H__TOOLBOX__GLYMPSE__

namespace Glympse
{
namespace Toolbox
{

/**
 * The class implements the logic necessary to ensure that all active tickets
 * are automatically "owned" by the attached instance of the Glympse Client API
 * platform when:
 *
 * * The instance of the platform is attached to this helper (if the instance
 *   has already been started and synchronized with the server).
 * * The instance of the attached platform completes its initial sync with the
 *   server.
 * * A new ticket is added to the platform.
 * * Manually requested by calling the refresh() method. This method should be
 *   called every time the host application comes to the foreground.
 */
/*O*public**/ class AutoOwnershipHelper : public Common< IEventListener >
{
    /**
     * Public section
     */

    /**
     * Constructs an auto-ownership helper for active, outgoing Glympse tickets.
     */
    public: AutoOwnershipHelper()
    {
        _glympse = NULL;
    }

    /**
     * Initializes the helper. Before starting the specified instance of the Glympse
     * Client API platform, ensure that sibling tickets have been enabled using the
     * allowSiblingTickets(true) API on GGlympse.
     *
     * @param glympse An instance of the Glympse Client API platform.
     */
    public: void attach(const GGlympse& glympse)
    {
        // If a Glympse Client API instance has already been attached, or the specified
        // instance is invalid, exit now.
        if (( NULL != _glympse ) || ( NULL == glympse ))
        {
            return;
        }

        // Cache the platform instance and subscribe to platform events.
        _glympse = glympse;
        _glympse->addListener(Object::fromThis(this));

        // Attempt a refresh of ticket ownership.
        refresh();
    }

    /**
     * Tears down the helper.
     */
    public: void detach()
    {
        // If the Glympse Client API instance was never initialized, exit now.
        if ( NULL == _glympse )
        {
            return;
        }

        // Unsubscribe from platform events and clear the platform reference.
        _glympse->removeListener(Object::fromThis(this));
        _glympse = NULL;
    }

    /**
     * Manually refreshes ownership of all active tickets and performs a server
     * synchronization to discover any new tickets.
     */
    public: void refresh()
    {
        // If no platform instance has been attached, or if that instance has
        // either not been started or has not completed its sync with the server,
        // exit now.
        if (( NULL == _glympse ) || !_glympse->isStarted() || !_glympse->getHistoryManager()->isSynced() )
        {
            return;
        }

        // Request ownership of all active tickets now.
        requestOwnership();

        // Perform a history refresh with the server to discover any new tickets
        // initiated by other platform instances.
        _glympse->getHistoryManager()->refresh();
    }

    /**
     * Private section
     */

    /**
     * Instance of the Glympse Client API platform.
     */
    private: GGlympse _glympse;

    /**
     * Requests ownership of all active tickets in the history manager.
     */
    private: void requestOwnership()
    {
        // Loop through all tickets in the history manager and request ownership.
        GArray<GTicket>::ptr tickets = _glympse->getHistoryManager()->getTickets();
        int count = tickets->length();
        for ( int index = 0 ; index < count ; index++ )
        {
            // If requesting ownership returns false, that means that the ticket
            // is not active. Since the history manager orders tickets active-owned,
            // followed by active-sibling, followed by inactive, we should be able
            // to safely stop looping here.
            if ( !requestOwnership(tickets->at(index)) )
            {
                break;
            }
        }
    }

    /**
     * Requests ownership of the specified ticket.
     *
     * @param ticket The ticket to own, if it's not already owned.
     * @returns true, if the ticket is active, false otherwise.
     */
    private: bool requestOwnership(const GTicket& ticket)
    {
        // If this ticket is not active, exit now and return false.
        if ( 0 == ( GC::TICKET_STATE_ACTIVATING & ticket->getState() ))
        {
            return false;
        }

        // If the specified ticket does not belong to me, request ownership now.
        if ( !ticket->isMine() )
        {
            ticket->own();
        }

        return true;
    }

    /**
     * IEventListener
     */

    /**
     * Handles events spread by the platform.
     */
    public: virtual void eventsOccurred(const GGlympse& glympse, int32 listener, int32 events, const GCommonObj& obj)
    {
        if ( GE::LISTENER_PLATFORM == listener )
        {
            // The platform has completed its sync with the server, so now is a good time
            // to automatically request ownership of all active tickets in our history.
            if ( 0 != ( events & GE::PLATFORM_SYNCED_WITH_SERVER ))
            {
                requestOwnership();
            }
            // A new ticket has been added to the platform - make sure that we own it.
            // For new tickets sent via this platform instance, we will already own it.
            // For sibling tickets sent by another platform instance, we will request
            // ownership (this may happen when refreshing history).
            else if ( 0 != ( GE::PLATFORM_TICKET_ADDED & events ))
            {
                if ( glympse->getHistoryManager()->isSynced() )
                {
                    requestOwnership((GTicket)obj);
                }
            }
        }
    }
};

}
}

#endif // !AUTOOWNERSHIPHELPER_H__TOOLBOX__GLYMPSE__
