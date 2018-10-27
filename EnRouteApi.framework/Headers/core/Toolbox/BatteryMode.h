//------------------------------------------------------------------------------
//
// Copyright (c) 2013 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef BATTERYMODE_H__TOOLBOX__GLYMPSE__
#define BATTERYMODE_H__TOOLBOX__GLYMPSE__

namespace Glympse 
{
namespace Toolbox
{

/**
 * The class implements on demand sharing policy. 
 */
/*O*public**/ class BatteryMode : public Common< IEventListener >
{
    /**
     * @name Constants/Defaults
     */
    
    /**
     * Regular (legacy) mode, where we used to drain battery as quickly as we can even,
     * when no one is actually viewing.
     */
    public: static const int32 MODE_REGULAR             = 0x1;

    /**
     * Platform is configured so that it almost does not drain any battery, when no one 
     * is viewing the user.
     *
     * @note As location profiles do not control post rate (it is dictated by server),
     * appropriate post rates should be specified for application API key to achieve 
     * the best result.
     */
    public: static const int32 MODE_SAVINGS             = 0x2;
    
    /**
     * Default mode.
     */
    public: static const int32 MODE_DEFAULT             = MODE_REGULAR;
    
    /**
     * Name of ticket property which is used to communicate local mode value to viewers.
     */
    public: static GString MODE_PROPERTY()
    {
        return CoreFactory::createString("battery_mode");
    }
    
    /**
     * Configures profile with id of CC::LOCATION_PROFILE_ACTIVE_NOT_WATCHED.
     *
     * See ILocationProfile for complete description of all configurable parameters.
     * See CoreConstants for related enumerations and defaults.
     */
    public: static GLocationProfile getActiveNotWatchedProfile()
    {
        GString os = CoreFactory::getOsName();
        if ( os->equals("ios") )
        {
            GLocationProfileBuilder builder = CoreFactory::createLocationProfileBuilder(CC::LOCATION_PROFILE_ACTIVE_NOT_WATCHED);
            builder->setMode(CC::LOCATION_MODE_ENABLED);
            builder->setDistance(1000.0);
            builder->setAccuracy(1000.0);
            builder->setActivity(1); // CLActivityTypeOther
            builder->setAutoPauseEnabled(false);
            return builder->getLocationProfile();
        }
        else if ( os->equals("android") )
        {
            GLocationProfileBuilder builder = CoreFactory::createLocationProfileBuilder(CC::LOCATION_PROFILE_ACTIVE_NOT_WATCHED);
            builder->setMode(CC::LOCATION_MODE_ENABLED);
            builder->setSource(CC::LOCATION_SOURCE_NETWORK | CC::LOCATION_SOURCE_PASSIVE);
            builder->setPriority(CC::LOCATION_PRIORITY_BALANCED_POWER_ACCURACY);
            builder->setDistance(1000.0);
            builder->setFrequency(60 * 1000);
            return builder->getLocationProfile();
        }
        // No other platforms are currently supported. 
        return NULL;
    }
    
    /**
     * Private members
     */
    
    /**
     * Instance of Glympse API platform.
     */
    private: GGlympse _glympse;
    
    /**
     * Configuration utility exposed by the platform. 
     */ 
    private: GConfig _config;
    
    /**
     * Battery manager.
     */
    private: GBatteryManager _batteryManager;
    
    /**
     * History manager.
     */
    private: GHistoryManager _historyManager;
    
    /**
     * Location manager.
     */
    private: GLocationManager _locationManager;

    /**
     * Current mode.
     */
    private: int32 _mode;
    
    /**
     * Preserved value of BatteryManager._isWakeLockEnabled before we modify it
     */
    private: bool _wasWakeLockEnabled;
    
    /**
     * @name Lifecycle tools
     */
    
    public: BatteryMode()
    {
        _mode = MODE_DEFAULT;
        _wasWakeLockEnabled = true;
    }
    
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
        _config = _glympse->getConfig();
        
        // Subscribe on platform events.
        GEventListener self = Object::fromThis(this);
        _glympse->addListener(self);
        _config->addListener(self);
        
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
        
        // Restore original platform state.
        if ( NULL != _batteryManager )
        {
            _batteryManager->enableWakeLock(_wasWakeLockEnabled);
        }
        
        // Unsubscribe from platform events.
        GEventListener self = Object::fromThis(this);
        if ( NULL != _locationManager )
        {
            _locationManager->removeListener(self);
        }
        _config->removeListener(self);
        _glympse->removeListener(self);
        
        // Forget platform and listener.
        _batteryManager = NULL;
        _historyManager = NULL;
        _locationManager = NULL;
        _config = NULL;
        _glympse = NULL;
    }
    
    private: void init()
    {
        GEventListener self = Object::fromThis(this);
        
        // Subscribe to location manager events
        _locationManager = _glympse->getLocationManager();
        _locationManager->addListener(self);
        
        // Load mode from platform config.
        loadMode();
        
        // Remember platform state
        _batteryManager = _glympse->getBatteryManager();
        _wasWakeLockEnabled = _batteryManager->isWakeLockEnabled();
        _historyManager = _glympse->getHistoryManager();
        
        // Apply original location manager configuration.
        configureProfiles();
        
        // Update battery manager
        updateWakeLock();
    }
    
    /**
     * @name Mode manipulation
     */
    
    /**
     * Applies new mode to platform and updates all currently active tickets. 
     */
    public: void setMode(int32 mode)
    {
        // Do nothing if platform is not attached.
        if ( NULL == _glympse )
        {
            return;
        }
        
        // Do nothing if no changes are required.
        if ( mode == _mode )
        {
            return;
        }
        
        // Remember new mode.
        _mode = mode;
        
        // Persist changes.
        saveMode();
        
        // It is only possible to proceed if platform is up and running.
        if ( !_glympse->isStarted() )
        {
            return;
        }
        
        // Configure location profiles accordingly.
        configureProfiles();
        
        // Update mode property on all currently active tickets.
        updateAllTickets();
        
        // Update battery manager
        updateWakeLock();
    }
    
    /**
     * Gets current mode. 
     */
    public: int32 getMode()
    {
        return _mode;
    }
    
    /**
     * @name Battery Manager Manipulation
     */
     
    /**
     *  Updates battery manager
     */
    private: void updateWakeLock()
    {
        // Do not toggle wake lock if it was disabled at the event of helper initialization.
        if ( !_wasWakeLockEnabled )
        {
            return;
        }
        
        if ( MODE_REGULAR == _mode )
        {
            return;
        }
        
        GLocationProfile profile = _locationManager->getCurrentProfile();
        if ( CC::LOCATION_PROFILE_ACTIVE_IS_WATCHED == profile->getProfile() )
        {
            _batteryManager->enableWakeLock(true);
        }
        else
        {
            _batteryManager->enableWakeLock(false);
        }
    }
    
    /**
     * @name Ticket manipulations
     */
    
    /**
     * The methods updates "mode" property on the ticket based on local _mode.
     */
    private: void updateTicket(const GTicket& ticket)
    {
        GString mode = NULL;
        if ( MODE_REGULAR == _mode )
        {
            mode = CoreFactory::createString("regular");
        }
        else if ( MODE_SAVINGS == _mode )
        {
            mode = CoreFactory::createString("savings");
        }
        if ( NULL == mode )
        {
            return;
        }
        ticket->appendData(0, MODE_PROPERTY(), CoreFactory::createPrimitive(mode));
    }
    
    /**
     * Updates mode property for all active tickets. 
     */
    private: void updateAllTickets()
    {
        GArray<GTicket>::ptr tickets = _glympse->getHistoryManager()->getTickets();
        int32 ticketsCount = tickets->length();
        for ( int32 ticketIndex = 0 ; ticketIndex < ticketsCount ; ++ticketIndex )
        {
            GTicket ticket = tickets->at(ticketIndex);
            if ( ticket->isActive() )
            {
                updateTicket(ticket);
            }
            else
            {
                break;
            }
        }
    }
    
    /**
     * @name Location profiles manipulation
     */
    
    /**
     * The method applies appropriate location manager settings based on currently enabled mode.
     * 
     * @note The method makes no affect if platform is not started yet.
     */
    private: void configureProfiles()
    {
        // Analyze the mode.
        if ( MODE_REGULAR == _mode )
        {
            // Just disable profiles to switch back to legacy behavior.
            _locationManager->enableProfiles(false);
        }
        else if ( MODE_SAVINGS == _mode )
        {
            // Enable profiles first.
            _locationManager->enableProfiles(true);
            
            // We only want to customize a profile relted to "sharing but not watched" state.
            GLocationProfile activeNotWatched = getActiveNotWatchedProfile();
            if ( NULL != activeNotWatched )
            {
                _locationManager->updateProfile(activeNotWatched);
            }
        }
        // No other modes are supported for now.
    }
    
    /**
     * @name Mode persistence
     *
     * The hierarchy of config properties:
     * ROOT                         : Object
     *     - PLATFORM_PROPERTIES    : Values/Objects/Arrays
     *     - app                    : Object
     *         - battery_mode       : int64(mode)           - See MODE_* values.
     */
    
    /**
     * Loads mode from platform config. 
     */
    private: void loadMode()
    {
        if ( NULL == _config )
        {
            _mode = MODE_DEFAULT;
            return;
        }
        GPrimitive contents = _config->getContents();
        if ( NULL == contents )
        {
            _mode = MODE_DEFAULT;
            return;
        }
        GPrimitive app = contents->get(CoreFactory::createString("app"));
        if ( NULL == app )
        {
            _mode = MODE_DEFAULT;
            return;
        }
        int32 mode = (int32)app->getLong(CoreFactory::createString("battery_mode"));
        _mode = ( 0 == mode ) ? MODE_DEFAULT : mode;
    }
    
    /**
     * Saves mode to platform config.
     */
    private: void saveMode()
    {
        // Check state.
        if ( NULL == _config )
        {
            return;
        }
        GPrimitive contents = _config->getContents();
        if ( NULL == contents )
        {
            return;
        }
        
        // Save mode.
        GPrimitive app = contents->get(CoreFactory::createString("app"));
        if ( NULL == app )
        {
            app = CoreFactory::createPrimitive(CC::PRIMITIVE_TYPE_OBJECT);
            contents->put(CoreFactory::createString("app"), app);
        }
        app->put(CoreFactory::createString("battery_mode"), (int64)_mode);
        
        // Save config. 
        _config->save();
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
            // Platform is synced with server.
            if ( 0 != ( GE::PLATFORM_SYNCED_WITH_SERVER & events ) )
            {
                // Simulate pre sync GE::PLATFORM_TICKET_ADDED events.
                glympse->getHistoryManager()->simulateAddedEvents(Object::fromThis(this));
            }
            
            // Ticket is added to the platform.
            else if ( 0 != ( GE::PLATFORM_TICKET_ADDED & events ) )
            {
                GTicket ticket = (GTicket)obj;                
                
                // Platform adds whole bunch of tickets from previous sessions at launch.
                // Only tickets that are still in ADDING state should be captured here.
                if ( 0 != ( GC::TICKET_STATE_ADDING & ticket->getState() ) )
                {
                    // Apply current mode to newly sent ticket.
                    updateTicket(ticket);
                }
            }
            
            // Platform is started.
            else if ( 0 != ( GE::PLATFORM_STARTED & events ) )
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
        else if ( GE::LISTENER_LOCATION == listener)
        {
            if ( 0 != ( GE::LOCATION_PROFILE_CHANGED & events ) )
            {
                updateWakeLock();
            }
        }
    }
};

}
}

#endif // !BATTERYMODE_H__TOOLBOX__GLYMPSE__


