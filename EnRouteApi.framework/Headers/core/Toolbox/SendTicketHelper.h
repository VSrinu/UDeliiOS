//------------------------------------------------------------------------------
//
// Copyright (c) 2013 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef SENDTICKETHELPER_H__TOOLBOX__GLYMPSE__
#define SENDTICKETHELPER_H__TOOLBOX__GLYMPSE__

namespace Glympse
{
namespace Toolbox
{

/*O*public**/ class SendTicketHelper : public Common< IEventListener >
{
    public: struct IListener : public ICommon
    {
        public: virtual void inviteReady(const GInvite& invite) = 0;
        public: virtual void inviteFailed() = 0;
        public: virtual void locationFailed() = 0;
    };
    /*C*/public: typedef O< IListener > GListener;/**/

    private: GGlympse _glympse;
    private: GListener _listener;
    private: GTicket _ticket;
    private: GLocationManager _locationManager;

    private: GRunnable _locationTimeout;

    public: static void send(const GGlympse& glympse, const GListener& listener,
        const GTicket& ticket, int64 locationTimeoutMillis)
    {
        new SendTicketHelper(glympse, listener, ticket, locationTimeoutMillis);
    }

    private: SendTicketHelper(const GGlympse& glympse, const GListener& listener,
        const GTicket& ticket, int64 locationTimeoutMillis)
    {
        _glympse = glympse;
        _listener = listener;
        _ticket = ticket;
        _ticket->addListener(Object::fromThis(this));

        _glympse->addListener(Object::fromThis(this));
        _locationManager = _glympse->getLocationManager();
        _locationManager->startLocation();

        _locationTimeout = new LocationTimeout(Object::fromThis(this));
        _glympse->getHandler()->postDelayed(_locationTimeout, locationTimeoutMillis);
    }

    private: void sendTicket()
    {
        if ( NULL == _ticket )
        {
            return;
        }
        _glympse->sendTicket(_ticket);
    }

    private: void cleanupLocationTimeout()
    {
        if ( NULL != _locationTimeout )
        {
            _glympse->getHandler()->cancel(_locationTimeout);
        }
        _locationTimeout = NULL;
    }

    private: void cleanupAll()
    {
        if ( NULL != _locationManager )
        {
            _locationManager->stopLocation(false);
        }
        _locationManager = NULL;
        if ( NULL != _ticket )
        {
            _ticket->removeListener(Object::fromThis(this));
        }
        _ticket = NULL;
        cleanupLocationTimeout();
    }

    private: void timeoutLocation()
    {
        _locationTimeout = NULL;
        cleanupAll();
        _listener->locationFailed();
    }

    /**
     * @name GEventListener section
     */

    /**
     * Handle events spread by the platform and ticket objects.
     */
    public: virtual void eventsOccurred(
        const GGlympse& glympse,
        int32 listener,
        int32 events,
        const GCommonObj& obj)
    {
        if ( GE::LISTENER_PLATFORM == listener )
        {
            if ( 0 != ( GE::PLATFORM_LOCATION ) )
            {
                _glympse->removeListener(Object::fromThis(this));
                cleanupLocationTimeout();
                sendTicket();
            }
        }
        else if ( GE::LISTENER_TICKET == listener )
        {
            if ( 0 != ( GE::TICKET_INVITE_CREATED & events ) )
            {
                cleanupAll();
                GTicket ticket = (GTicket)obj;
                GArray<GInvite>::ptr invites = ticket->getInvites();
                int numInvites = ( NULL == invites ) ? 0 : invites->length();
                for ( int i = 0; i < numInvites; i++ )
                {
                    GInvite invite = ticket->getInvites()->at(i);
                    _listener->inviteReady(invite);
                }
            }
            if ( 0 != ( ( GE::TICKET_REQUEST_FAILED  | GE::TICKET_FAILED ) & events ) )
            {
                cleanupAll();
                GTicket ticket = (GTicket)obj;
                _listener->inviteFailed();
            }
            if ( 0 != ( GE::TICKET_INVITE_FAILED & events ) )
            {
                cleanupAll();
                GTicket ticket = (GTicket)obj;
                ticket->modify(0, NULL, NULL);
                _listener->inviteFailed();
            }
        }
    }

    private: class LocationTimeout : public Common< IRunnable >
    {
        private: O<SendTicketHelper> _helper;

        public: LocationTimeout(const O<SendTicketHelper>& helper)
        {
            _helper = helper;
        }

        public: /*S*override**/ void run()
        {
            _helper->timeoutLocation();
        }
    };
};

}
}

#endif // SENDTICKETHELPER_H__TOOLBOX__GLYMPSE__
