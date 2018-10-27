//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ILOCATION_H__GLYMPSE__
#define ILOCATION_H__GLYMPSE__

namespace Glympse 
{
        
/*C*/
struct ILocation;
typedef O< ILocation > GLocation;
/**/

/**
 * Specifies a single location point (latitude and longitude) at a given time, 
 * with optional altitude, bearing, speed, and accuracy information.
 */
/*O*public**/ struct ILocation : public ILatLng
{
    /**
     * True if this location has a provider.
     */
    public: virtual bool hasProvider() = 0;
    
    /**
     * True if this location has an altitude.
     */
    public: virtual bool hasAltitude() = 0;    
    
    /**
     * True if this location has a bearing.
     */
    public: virtual bool hasBearing() = 0;    
    
    /**
     * True if this location has a speed.
     */
    public: virtual bool hasSpeed() = 0;    
    
    /**
     * True if this location has horizontal accuracy.
     */
    public: virtual bool hasHAccuracy() = 0;    

    /**
     * True if this location has vertical accuracy.
     */
    public: virtual bool hasVAccuracy() = 0;        
    
    /**
     * True if this location has a time.
     */
    public: virtual bool hasTime() = 0;

    /**
     * Get the provider if available.
     * If this location does not have a provider then -1 is returned.
     */
    public: virtual int32 getProvider() = 0;

    /**
     * Get the altitude if available, in meters above sea level.
     *
     * If this location does not have an altitude then Float#NaN is returned.
     */
    public: virtual float getAltitude() = 0;

    /**
     * Get the bearing, in degrees.
     *
     * Bearing is the horizontal direction of travel of this device, and is not related to the device orientation. 
     * It is guaranteed to be in the range (0.0, 360.0] if the device has a bearing.
     *
     * If this location does not have a bearing then Float#NaN is returned.
     */
    public: virtual float getBearing() = 0;
    
    /**
     * Get the speed if it is available, in meters/second over ground.
     *
     * If this location does not have a speed then Float#NaN is returned.
     */
    public: virtual float getSpeed() = 0;
    
    /**
     * Get the estimated horizontal accuracy of this location, in meters.
     *
     * If this location does not have an accuracy then Float#NaN is returned.
     */
    public: virtual float getHAccuracy() = 0;

    /**
     * Get the estimated vertical accuracy of this location, in meters.
     *
     * If this location does not have an accuracy then Float#NaN is returned.
     */
    public: virtual float getVAccuracy() = 0;
    
    /**
     * Return the UTC time of this fix, in milliseconds since January 1, 1970.
     */
    public: virtual int64 getTime() = 0;    
    
    /**
     * Creates and returns a copy of this location object.
     */
    public: virtual GLocation clone() = 0;        

    /**
     * Returns the approximate distance in meters between this location and the given location. 
     * Distance is defined using the WGS84 ellipsoid.
     *
     * @param dest The destination location.
     * @return The approximate distance in meters.
     */
    public: virtual float distanceTo(const GLatLng& dest) = 0;
    
    /**
     * Returns the approximate initial bearing in degrees East of true North when traveling along the shortest path 
     * between this location and the given location. The shortest path is defined using the WGS84 ellipsoid. 
     * Locations that are (nearly) antipodal may produce meaningless results.
     *
     * @param dest The destination location.
     * @return The initial bearing in degrees.
     */
    public: virtual float bearingTo(const GLatLng& dest) = 0;
};
    
}

#endif // !ILOCATION_H__GLYMPSE__
