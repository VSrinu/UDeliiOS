//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ILOCATIONMANAGER_H__GLYMPSE__
#define ILOCATIONMANAGER_H__GLYMPSE__

namespace Glympse 
{
    
/**
 * Provides a chance to control and customize location subsystem. 
 */
/*O*public**/ struct ILocationManager : public IEventSink
{
    /**
     * Provides the most recent location.
     */ 
    public: virtual GLocation getLocation() = 0;
    
    /**
     * Enables tracking user's location, when there are no outgoing tickets.
     * This feature is useful to display user on the map, even if he/she is not
     * broadcasting a location. It is also useful to have a chance to turn this
     * feature off, when user location is not required any more (or not required
     * at all for UI purposes). See stopLocation() for details. 
     *
     * Calling this method several times in succession result in increasing internal counter of
     * consumers of location updates. Corresponding amount of calls to stopLocation()
     * should be made to disable location updates completely.
     *
     * This option does not override global location sharing preference.
     * It is still possible to send a ticket and upload locations,
     * even if this feature is turned off.
     *
     * Glympse API only keep location services started when application is
     * running in the foreground (taking into account that there are no active outgoing tickets). 
     * This mechanism in not intended to provide host application with location updates
     * when running in the background. 
     *
     * Location services are disabled by default.
     *
     * @return Returns a number of times stopLocation() needs to be called to stop
     * location updates. 
     */
    public: virtual int32 startLocation() = 0;
    
    /**
     * Stops location updates previously started by startLocation().
     * It is required to make this call as many times as startLocation() was called
     * to stop location updates completely.
     *
     * Location manager will keep up and running, if there are any active outgoing 
     * tickets on the system. 
     *
     * @param forced Allows to stop underlying location provider unconditionally
     * (indifferently from a number of preceding calls to startLocation()).
     * @return Returns how many more invocations of stopLocation() are required to stop
     * location updates. 
     */
    public: virtual int32 stopLocation(bool forced) = 0;
    
    /**
     * Overrides default location provider.
     */ 
    public: virtual void setLocationProvider(const GLocationProvider& locationProvider) = 0;
    
    /**
     * Overrides default proximity provider.
     */
    public: virtual void setProximityProvider(const GProximityProvider& proximityProvider) = 0;
    
    /**
     * Gets current location state. 
     * See CoreConstants for more details. 
     */
    public: virtual int32 getLocationState() = 0;
    
    /**
     * Controls the use of location profiles. 
     * 
     * This feature is disabled by default.
     */
    public: virtual void enableProfiles(bool enable) = 0;
    
    /**
     * Checks if profiles are enabled. 
     */
    public: virtual bool areProfilesEnabled() = 0;
    
    /**
     * Provides manager with externally configured location profile. Location profile object 
     * refers to specific profile identifier.
     *
     * This profile is not applied to location provder right away. Location manager pick correct 
     * profile to apply based on library state. This method is only used to update profile properties
     * for specific profile identifier. 
     *
     * @param Location profile to be updated.
     * @return true on success.
     */
    public: virtual bool updateProfile(const GLocationProfile& profile) = 0;
    
    /**
     * Gets currently applied location profile. 
     *
     * @return Profile object or NULL if profiles are disabled.
     */
    public: virtual GLocationProfile getCurrentProfile() = 0;
    
    /**
     * Gets currently applied profile via identifier. 
     * 
     * @param profileId Profile identifier. See CC::LOCATION_PROFILE_* for details.
     * @return Profile object or NULL if profiles are disabled on profile ID is incorrect.
     */
    public: virtual GLocationProfile getProfile(int profileId) = 0;
    
    /**
     * Client API performs location filtering to ignore knowingly bogus points.
     * This method can be used to enable/disable the feature.
     *
     * Filtering is ebabled by default.
     *
     * @param enable Filtering mode.
     */
    public: virtual void enableFiltering(bool enable) = 0;
    
    /**
     * Checks is local filtering is enabled.
     */
    public: virtual bool isFilteringEnabled() = 0;
    
    /**
     * Notifies the platform that geofence transition occurred while platform was not running.
     *
     * @param regionId Identifier of geofencing region.
     * @param transition Type of transition. Can be one of CC::GEOFENCE_TRANSITION_* values.
     */
    public: virtual void handleGeofence(const GString& regionId, int32 transition) = 0;
};
    
/*C*/typedef O< ILocationManager > GLocationManager;/**/
    
}

#endif // !ILOCATIONMANAGER_H__GLYMPSE__
