//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IBATTERYMANAGER_H__GLYMPSE__
#define IBATTERYMANAGER_H__GLYMPSE__

namespace Glympse 
{
    
/**
 * Provides basic facilities for battery management in Glympse API. 
 */
/*O*public**/ struct IBatteryManager : public IEventSink
{
    /**
     * Sets the battery levels that the Glympse API should use when detecting low and good battery states.
     *
     * The Glympse API monitors the device's battery level and external power state.
     * If the device is not on external power and drops below the 'low battery' level,
     * then the Glympse API will automatically suspend all location and network activity
     * in order to preserve power.
     * 
     * The Glympse API will suspend location and network activity when not on external power and
     * the battery level is less than or equal to lowBatteryLevel. Glympse will
     * resume these location and network activity (if needed) when on external power or the battery
     * level is greater than or equal to goodBatteryLevel. The default values are
     * 0 for lowBatteryLevel and 100 for goodBatteryLevel. This means that battery monitoring feature
     * is disabled by default.
     * 
     * @param lowBatteryLevel The low battery level. 0 to disable battery monitoring. Valid values are (0 <= lowBatteryLevel <= goodBatteryLevel)
     * @param goodBatteryLevel The good battery level. Valid values are (lowBatteryLevel <= goodBatteryLevel <= 100)
     * @return true, if the parameters passed in are valid.
     */ 
    public: virtual bool setBatteryLevels(int32 lowBatteryLevel, int32 goodBatteryLevel) = 0;
    
    /**
     * Checks if the Glympse API can run with the current battery level and power state.
     * 
     * The Glympse API monitors the device's battery level and external power state.
     * If the device is not on external power and drops below the 'low battery' level,
     * then the Glympse API will automatically suspend all location and network activity
     * in order to preserve power. The good/low battery levels can be set by calling the
     * setBatteryLevels method.
     * 
     * If you register a IEventListener with the IBatteryManager,
     * you can listen for the GC::BATTERY_STATE_CHANGED event to be notified when the battery state changes.
     *
     * @return true, if the battery level is above the 'low battery" level or the device is connected to external power.
     */ 
    public: virtual bool isBatteryLevelGood() = 0;
    
    /**
     * Return true if the battery is good or the user has approved us to run with a low battery.    
     */
    public: virtual bool isBatteryOk() = 0;
    
    /**
     * Return true if the user has approved us to run with a low battery.
     */
    public: virtual bool isBatteryForce() = 0;    
    
    /**
     * Provides a chance to override battery state, if it turns into bad state.
     * It is required, if you want to continue transmitting and receiving location updates even in bad battery state.
     */
    public: virtual void setBatteryForce() = 0;
    
    /**
     * Returns true if it is currently ok for the system to acquire a wake lock
     */
    public: virtual bool isWakeLockEnabled() = 0;
    
    /**
     * Sets whether or not the system should be able to acquire a wake lock. 
     * Since this method may be called at any time, it also checks the system state
     * and acquires or releases an existing wake lock when appropriate.
     */
    public: virtual void enableWakeLock(bool wakeLockEnabled) = 0;
};
    
/*C*/typedef O< IBatteryManager > GBatteryManager;/**/
    
}

#endif // !IBATTERYMANAGER_H__GLYMPSE__
