//------------------------------------------------------------------------------
//
// Copyright (c) 2014 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef AIRPLANEMODE_H__TOOLBOX__GLYMPSE__
#define AIRPLANEMODE_H__TOOLBOX__GLYMPSE__

namespace Glympse
{
namespace Toolbox
{

/**
 * Provides helpers for supporting airplane mode.
 *
 * @note This helper enables handoff functionality automatically without prompting user.
 */
/*O*public**/ class AirplaneMode : public Common< IEventListener >
{
    /**
     * @name Constants/Defaults
     */
    
    /**
     * Provider identifier associated woth Gogo.
     */
    public: static GString GOGO_PROVIDER_ID()
    {
        return CoreFactory::createString("gogo");
    }
    
    /**
     * @name Private members
     */
    
    /**
     * Instance of Glympse API platform.
     */
    private: GGlympse _glympse;
    
    /**
     * An instance of handoff manager.
     */
    private: GHandoffManager _handoffManager;
    
    /**
     * Life cycle methods
     */
    
    /**
     * Initializes the helper.
     *
     * @param glympse Instance of Glympse platform.
     */
    public: void attach(const GGlympse& glympse)
    {
        if ( ( NULL != _glympse ) || ( NULL == glympse ) )
        {
            // Already initialized or invalid arguments.
            return;
        }
        
        // Remember platform.
        _glympse = glympse;
        
        // Subscribe on platform events.
        GEventListener self = Object::fromThis(this);
        _glympse->addListener(self);
        
        // We want to delay initialization up until the moment when platform is started.
        if ( glympse->isStarted() )
        {
            // Initialize component state.
            init();
        }
    }
    
    /**
     * Tears down the component.
     */
    public: void detach()
    {
        if ( NULL == _glympse )
        {
            // Not yet initialized.
            return;
        }
        
        // Unsubscribe from platform events.
        GEventListener self = Object::fromThis(this);
        _glympse->removeListener(self);
        if ( NULL != _handoffManager )
        {
            _handoffManager->removeListener(self);
        }
        
        // Forget prefetched objects.
        _handoffManager = NULL;
        _glympse = NULL;
    }
    
    private: void init()
    {
        GEventListener self = Object::fromThis(this);
        
        // Subscribe to handoff manager events.
        _handoffManager = _glympse->getHandoffManager();
        _handoffManager->addListener(self);
    }
    
    /**
     * @name Helper functions
     */
    
    /**
     * Checks if a user is currently on a plane.
     */
    public: bool isOnPlane(const GUser& user)
    {
        if ( user->isSelf() )
        {
            return isOnPlane();
        }
        else
        {
            return isSentFromPlane(user->getActiveStandalone());
        }
    }
    
    /**
     * Checks if self user is currently on a plane.
     */
    public: bool isOnPlane()
    {
        if ( NULL == _handoffManager )
        {
            return false;
        }
        GHandoffProvider handoffProvider = _handoffManager->getHandoffProvider();
        if ( NULL == handoffProvider )
        {
            return false;
        }
        return handoffProvider->getProviderId()->equals(GOGO_PROVIDER_ID());
    }
    
    /**
     * Checks if the ticket was sent from a plane.
     */
    public: bool isSentFromPlane(const GTicket& ticket)
    {
        if ( NULL == ticket )
        {
            return false;
        }
        GTravelMode travelMode = ticket->getTravelMode();
        if ( NULL == travelMode )
        {
            return false;
        }
        return ( travelMode->getMode() == GC::TRAVEL_MODE_AIRLINE );
    }
    
    /**
     * @name IEventListener section
     */
    
    /**
     * Handle events spread by the platform and config objects.
     */
    public: virtual void eventsOccurred(const GGlympse& glympse, int32 listener, int32 events, const GCommonObj& obj)
    {
        // Events spread by the platform.
        if ( GE::LISTENER_PLATFORM == listener )
        {
            // Platform is started.
            if ( 0 != ( GE::PLATFORM_STARTED & events ) )
            {
                // Perform initialization.
                init();
            }
            
            // Platform is stopped. This is really a corner case.
            else if ( 0 != ( GE::PLATFORM_STOPPED & events ) )
            {
                detach();
            }
        }
        
        // Events spread by the handoff manager.
        if ( GE::LISTENER_HANDOFF == listener )
        {
            // Handoff provider is available.
            if ( 0 != ( GE::HANDOFF_PROVIDER_AVAILABLE & events ) )
            {
                GHandoffProvider handoffProvider = (GHandoffProvider)obj;
                if ( handoffProvider->isHandoffAvailable() )
                {
                    if ( !handoffProvider->isHandoffAllowed() )
                    {
                        // Allow handoff without confirmint it with the user.
                        // Host application can choose to implement different approval policy.
                        handoffProvider->allowHandoff();
                    }
                }
            }
        }
    }
};

}
}

#endif // !AIRPLANEMODE_H__TOOLBOX__GLYMPSE__
