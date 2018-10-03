//------------------------------------------------------------------------------
//
// Copyright (c) 2014 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IDIRECTIONSMANAGER_H__GLYMPSE__
#define IDIRECTIONSMANAGER_H__GLYMPSE__

namespace Glympse
{
    
/**
 * Controls the behavior of ETA/directions unit.
 *
 * The functionality exposed by IDirectionsManager is enabled only when platform is responsible
 * for calculting directions (GC::ETA_MODE_INTERNAL mode is set through IGlympse#setEtaMode()).
 */
/*O*public**/ struct IDirectionsManager : public ICommon
{
    /**
     * Enables automatic device activity recognition.
     *
     * The feature is disabled by default.
     *
     * Supported platforms:
     * - iOS 7.0+
     * - Android 2.3+ with Google Play Services 4.x+
     *
     * @note This method does not trigger directions to be recalculated instantaneously.
     * It only affects the behavior of activity recognition unit, which can in turn
     * stimulate route update.
     *
     * @note Activity recognition remains enabled only for the duration of sharing.
     *
     * @param enable Flag indicating whether activity recognition should be enabled.
     */
    public: virtual void enableActivityRecognition(bool enable) = 0;
    
    /**
     * @return true if automatic activity recognition is enabled.
     */
    public: virtual bool isActivityRecognitionEnabled() = 0;
    
    /**
     * Gets the most recently recognized device activity.
     *
     * @return Current device activity, which will be one of the CC#ACTIVITY_* constants.
     */
    public: virtual int32 getDeviceActivity() = 0;
    
    /**
     * Determines if device is stationary. Activity recognition must be enabled.
     *
     * @return true if device is being held still.
     */
    public: virtual bool isDeviceStationary() = 0;
    
    /**
     * Overrides currently applied travel mode. The mode can only be overridden if
     * all of the following criteria are met:
     * - Internal ETA calculation is enabled (see IGlympse#setEtaMode()).
     * - Automatic activity recognition is disabled (see enableActivityRecognition()).
     *
     * The following travel modes are supported by this method:
     * - GC#TRAVEL_MODE_DEFAULT
     * - GC#TRAVEL_MODE_DRIVE
     * - GC#TRAVEL_MODE_CYCLE
     * - GC#TRAVEL_MODE_WALK
     * - GC#TRAVEL_MODE_TRANSIT
     *
     * @note Calling this method causes routes to all destinations to be recalculated
     * for all active tickets.
     *
     * @param mode Travel mode to be used for querying directions.
     */
    public: virtual void setTravelMode(int32 mode) = 0;
    
    /**
     * Gets the most recently applied travel mode.
     *
     * @return Travel mode, which will be one of the GC#TRAVEL_MODE_* constants.
     */
    public: virtual int32 getTravelMode() = 0;
    
    /**
     * Determines when etas and routes should be queried for outgoing tickets.
     *
     * @param mode Desired query mode, one of the GC#ETA_QUERY_MODE_* constants.
     */
    public: virtual void setEtaQueryMode(int32 mode) = 0;
    
    /**
     * Gets the currently set eta/route query mode
     *
     * @return Eta/route query mode, which will be one of the GC#ETA_QUERY_MODE_* constants.
     */
    public: virtual int32 getEtaQueryMode() = 0;

    /**
     * Initiates a request for directions. A listener should be set on the returned Directions object to listen for the response.
     *
     * @param origin Starting point for directions.
     * @param destination Ending point for directions.
     * @param travelMode Travel Mode to be used for the directions. See GC#TRAVEL_MODE_*
     * @return Directions object with results. Set a listener on value to determine when results are ready. If the
     *     returned value is NULL, then there was an issue with the parameters and the query was not performed.
     */
    public: virtual GDirections queryDirections(const GLatLng& origin, const GLatLng& destination, int32 travelMode) = 0;
};
    
/*C*/typedef O< IDirectionsManager > GDirectionsManager;/**/
    
}

#endif // !IDIRECTIONSMANAGER_H__GLYMPSE__
