//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ILOCATIONPROFILE_H__GLYMPSE__
#define ILOCATIONPROFILE_H__GLYMPSE__

namespace Glympse
{

/**
 * A location profile defines the configuration that should be applied to the location provider
 * for one of a set of pre-defined Glympse platform states. They are:
 * 
 * - Glympse is running in the background with no active outgoing tickets.
 * - Glympse is running in the foreground with no active outgoing tickets.
 * - Glympse is running (foreground or background) with at least one active outgoing ticket, but with ZERO watchers.
 * - Glympse is running (foreground or background) with at least one active outgoing ticket and at least one watcher.
 *
 * Location profiles are intended to provide the host application with an opportunity to tune the 
 * behavior of the location provider in order to minimize battery consumption.
 *
 * Profiles are created using the GLocationProfileBuilder object.
 * Profiles are applied using ILocationManager#updateProfile().
 */
/*O*public**/ struct ILocationProfile : public IComparable
{
    /**
     * Profile identifier - one of the CC::LOCATION_PROFILE_* values.
     */
    public: virtual int32 getProfile() = 0;
    
    /**
     * Indicates whether the location provider should be started when the profile is applied.
     *
     * - Platform:    iOS, Android
     * - Type:        int32
     * - Values:      One of the CC::LOCATION_MODE_* values.
     */
    public: virtual int32 getMode() = 0;
    
    /**
     * Specifies which source(s) should be used to query location data.
     * 
     * - Platform:    Android, BB
     * - Type:        int32 (bitmask)
     * - Values:      Any combination of CC::LOCATION_SOURCE_* values.
     */
    public: virtual int32 getSource() = 0;
    
    /**
     * The minimum distance between location updates.
     *
     * - Platform:    iOS, Android, WinPhone
     * - Type:        double
     * - Values (iOS):
     *   -   kCLDistanceFilterNone  = -1
     *   -   Distance in meters
     * - Applied to (iOS):      CLLocationManager.distanceFilter
     * - Values (Android):
     *   -   BEST                   = 0
     *   -   Distance in meters
     * - Applied to (Android):  LocationManager.requestLocationUpdates(..., float minDistance, ...)
     * - Values (Fuse):
     *   -   BEST                   = 0
     *   -   Distance in meters
     *   Applied to (Fuse):     LocationRequest.setSmallestDisplacement(float displacement)
     * - Values (WinPhone):
     *   -   BEST                   = 0
     *   -   Distance in meters
     * - Applied to (WinPhone):  Geolocator.MovementThreshold
     */
    public: virtual double getDistance() = 0;

    /**
     * The desired accuracy of the location data.
     *
     * - Platform:    iOS, BB, WinPhone
     * - Type:        double
     * - Values (iOS):
     *   -   kCLLocationAccuracyBestForNavigation   = -2
     *   -   kCLLocationAccuracyBest                = -1
     *   -   Distance in meters [0..3000]
     * - Applied to (iOS):        CLLocationManager.desiredAccuracy
     * - Values (BB):
     *   -   UNSPECIFIED (Best)                     = 0
     *   -   Distance in meters
     * - Applied to (BB):   QGeoPositionInfoSource.setProperty("accuracy", float distance);
     * - Values (WinPhone):
     *   -   PositionAccuracy.High      = ...internal mapping... = -2
     *   -   PositionAccuracy.Default   = ...internal mapping... = -1
     * - Applied to (WinPhone):   Geolocator.DesiredAccuracy
     * - Values (WinPhone Alternate):
     *   -   Distance in meters [0..3000]
     * - Applied to (WinPhone Alternate):   Geolocator.DesiredAccuracyInMeters
     */
    public: virtual double getAccuracy() = 0;
    
    /**
     * The minimum time interval between location updates.
     *
     * - Platform:    Android, BB, WinPhone
     * - Type:        int32
     * - Values (Android):
     *   -   BEST                       = 0
     *   -   Time in milliseconds
     * - Applied to (Android):  LocationManager.requestLocationUpdates(..., long minTime, ...)
     * - Values (Fuse):
     *   -   BEST                       = 0
     *   -   Time in milliseconds
     *   Applied to (Fuse):     LocationRequest.setInterval(long interval)
     * - Values (BB):
     *   -   UNSPECIFIED (Best)         = 0
     *   -   Time in milliseconds
     * - Applied to (BB):       QGeoPositionInfoSource.setUpdateInterval(int32 minTime)
     * - Values (WinPhone):
     *   -   BEST                       = 0
     *   -   Time in milliseconds
     * - Applied to (WinPhone):  Geolocator.ReportInterval
     */
    public: virtual int32 getFrequency() = 0;
    
    /**
     * Identifies how importants location updates are.
     *
     * - Platform:    Android (Fuse)
     * - Type:        int32
     * - Values:
     *   -   PRIORITY_HIGH_ACCURACY               = 100  (default)
     *   -   PRIORITY_BALANCED_POWER_ACCURACY     = 102
     *   -   PRIORITY_NO_POWER                    = 105
     * - Applied to:  LocationResult.setPriority(int priority)
     */
    public: virtual int32 getPriority() = 0;
    
    /**
     * The type of user activity associated with the location updates.
     *
     * - Platform:    iOS (6.0+)
     * - Type:        int32 (CLActivityType)
     * - Values:
     *   -   CLActivityTypeOther                  = 1  (default)
     *   -   CLActivityTypeAutomotiveNavigation   = 2
     *   -   CLActivityTypeFitness                = 3
     *   -   CLActivityTypeOtherNavigation        = 4
     * - Applied to:  CLLocationManager.activityType
     */
    public: virtual int32 getActivity() = 0;
    
    /**
     * A bool value indicating whether the location provider object may pause location updates.
     *
     * - Platform:    iOS (6.0+)
     * - Type:        bool
     * - Values:      true/false
     * - Applied to:  LocationManager.pausesLocationUpdatesAutomatically
     */
    public: virtual bool isAutoPauseEnabled() = 0;
    
    /**
     * A bool value whether location provider object should enabled Significant Location Change Monitoring.
     *
     * - Platform:    iOS (4.0+)
     * - Type:        bool
     * - Values:      true/false
     * - Applied to:  LocationManager start/stopMonitoringSignificantLocationChanges()
     */
    public: virtual bool isSignificantLocationChangeMonitoringEnabled() = 0;
};
    
/*C*/typedef O< ILocationProfile > GLocationProfile;/**/
    
}

#endif // !ILOCATIONPROFILE_H__GLYMPSE__
