//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ITRACK_H__GLYMPSE__
#define ITRACK_H__GLYMPSE__

namespace Glympse 
{
 
/**
 * Represents a collection of location points (ILocation).
 *
 * Notes to map control implementors:
 * - Trail can be modified (and trimmed) by the library in unpredicteable way. 
 *   Any part of it can be changed at any time.
 * - The safest way to draw the trail is to use getLocations() method and update the whole trail
 *   during each drawing cycle. 
 * - It is stil possible to rely on updates (coming from getNewLocations()).
 * - The entire trail needs to be redrawn, if getNewLocations() returns NULL or empty list
 *   while GE#TICKET_TRACK_CHANGED is being spread.
 */
/*O*public**/ struct ITrack : public virtual ICommon
{
    /**
     * A number of location points in main portion of a trail (returned by getLocations()).
     */
    public: virtual int32 length() = 0;
    
    /**
     * Returns the list of location that make up the trail.
     *
     * @return List object containint trail. The object cannot be NULL, but can be empty. 
     */
    public: virtual GList<GLocation>::ptr getLocations() = 0;
    
    /**
     * Returns new portion of the trail (pulled from server during latest sync).
     *
     * @return List object containing new portion of the trail. The object can be NULL. 
     */
    public: virtual GList<GLocation>::ptr getNewLocations() = 0;
    
    /**
     * Gets track distance in meters.
     * 
     * @return Track distance or 0, if distance is unknown.
     */
    public: virtual int32 getDistance() = 0;
};
    
/*C*/typedef O< ITrack > GTrack;/**/
    
}

#endif // !ITRACK_H__GLYMPSE__
