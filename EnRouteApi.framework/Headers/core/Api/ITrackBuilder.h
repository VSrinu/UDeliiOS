//------------------------------------------------------------------------------
//
// Copyright (c) 2014 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ITRACKBUILDER_H__GLYMPSE__
#define ITRACKBUILDER_H__GLYMPSE__

namespace Glympse
{
    
/**
 * The interface to construct and initialize track objects.
 *
 * It is recommended to construct track builder objects and populate it with location data
 * on background thread from performance considerations. Parsing track information and 
 * converting it in an alternative representation can be pretty resource consuming operation.
 *
 * However, applying it to the platform (by calling ITicket#updateRoute) has to be done
 * on the same thread where platform was instantiated.
 */
/*O*public**/ struct ITrackBuilder : public virtual ICommon
{
    /**
     * Adds location to the track.
     *
     * @param location Location object to add.
     */
    public: virtual void addLocation(const GLocation& location) = 0;
        
    /**
     * Specifies track source.
     *
     * See GC::TRACK_SOURCE_* for the list of supported sources or contact 
     * partners@glympse.com, if any particular source is not on the list yet.
     * 
     * @param source The source of track data.
     */
    public: virtual void setSource(int32 source) = 0;
    
    /**
     * Specifies track distance.
     *
     * @param distance Track distance in meters.
     */
    public: virtual void setDistance(int32 distance) = 0;
    
    /**
     * Calculates track distance based on location data already populated.
     */
    public: virtual void calculateDistance() = 0;
        
    /**
     * Returns track object constructed by the builder.
     *
     * @return Prepared track object.
     */
    public: virtual GTrack getTrack() = 0;
};
    
/*C*/typedef O< ITrackBuilder > GTrackBuilder;/**/
    
}

#endif // !ITRACKBUILDER_H__GLYMPSE__
