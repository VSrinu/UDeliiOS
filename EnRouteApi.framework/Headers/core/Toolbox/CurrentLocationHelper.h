//------------------------------------------------------------------------------
//
// Copyright (c) 2013 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef CURRENTLOCATIONHELPER_H__TOOLBOX__GLYMPSE__
#define CURRENTLOCATIONHELPER_H__TOOLBOX__GLYMPSE__

namespace Glympse
{
namespace Toolbox
{

/*O*public**/ class CurrentLocationHelper : public Common< IEventListener >
{
    public: struct IListener : public ICommon
    {
        // Both of these functions expect a return value which tells the helper whether to keep
        // going with location or whether to stop.

        /**
         * Gives a location value which should be evaluated.
         * @param Location returned by system.
         * @return whether the location helper should continue trying to get points.
         */
        public: virtual bool isLocationSatisfactory(const GLocation& location) = 0;

        /**
         * Informs listener that the timeout occurred and that no location points have
         * been gathered in that time. 
         * @return whether the location helper should continue trying to get points.
         */
        public: virtual bool locationTimeout() = 0;

        /**
         * Informs listener that an error occurred. It could be that invalid parameters were
         * passed or glympse is stopped. The helper will be shut down if this callback occurs.
         * @return whether the location helper should continue trying to get points.
         */
        public: virtual void locationError() = 0;
    };
    /*C*/public: typedef O< IListener > GListener;/**/

    private: GGlympse _glympse;
    private: GListener _listener;
    private: GLocationManager _locationManager;
    private: int64 _locationTimeoutMillis;

    private: GRunnable _locationTimeout;

    public: static bool getLocation(const GGlympse& glympse, const GListener& listener,
        int64 locationTimeoutMillis)
    {
        if ( NULL == glympse || !glympse->isStarted() )
        {
            listener->locationError();
            return false;
        }

        GLocationManager locationManager = glympse->getLocationManager();
        GLocation location = locationManager->getLocation();
        if ( listener->isLocationSatisfactory(location) )
        {
            return false;
        }
        new CurrentLocationHelper(glympse, listener, locationTimeoutMillis);
        return true;
    }

    private: CurrentLocationHelper(const GGlympse& glympse, const GListener& listener,
        int64 locationTimeoutMillis)
    {
        _glympse = glympse;
        _listener = listener;
        _locationTimeoutMillis = locationTimeoutMillis;

        _glympse->addListener(Object::fromThis(this));
        _locationManager = _glympse->getLocationManager();
        _locationManager->startLocation();

        setLocationTimeout();
    }

    private: void setLocationTimeout()
    {
        _locationTimeout = new LocationTimeout(Object::fromThis(this));
        _glympse->getHandler()->postDelayed(_locationTimeout, _locationTimeoutMillis);
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
        cleanupLocationTimeout();
        _glympse->removeListener(Object::fromThis(this));
    }

    private: void timeoutLocation()
    {
        _locationTimeout = NULL;
        if ( NULL == _locationManager )
        {
            // Already cleared. Ignore this timeout.
            return;
        }

        if ( _listener->locationTimeout() )
        {
            // Shutdown the helper.
            cleanupAll();
            return;
        }

        // Keep going with location.
        setLocationTimeout();
    }

    /**
     * @name GEventListener section
     */

    /**
     * Handle events spread by the platform.
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
                cleanupLocationTimeout();
                GLocation location = _locationManager->getLocation();
                if ( _listener->isLocationSatisfactory(location) )
                {
                    cleanupAll();
                }
                else
                {
                    setLocationTimeout();
                }
            }
        }
    }

    private: class LocationTimeout : public Common< IRunnable >
    {
        private: O<CurrentLocationHelper> _helper;

        public: LocationTimeout(const O<CurrentLocationHelper>& helper)
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

#endif // CURRENTLOCATIONHELPER_H__TOOLBOX__GLYMPSE__
