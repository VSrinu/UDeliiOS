//------------------------------------------------------------------------------
//
// Copyright (c) 2016 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IDIRECTIONS_H__GLYMPSE__
#define IDIRECTIONS_H__GLYMPSE__

namespace Glympse 
{
    
/**
 * Represents a set of directions.
 */
/*O*public**/ struct IDirections : public IEventSink
{
    /**
     * Gets the state of the directions. See GC::DIRECTIONS_STATE_*.
     */
    public: virtual int32 getState() = 0;

    /**
     * Gets the time the direction request was made.
     */         
    public: virtual int64 getRequestTime() = 0;

    /**
     * Gets directions origin location.
     * @return GLatLng object or NULL.
     */         
    public: virtual GLatLng getOrigin() = 0;

    /**
     * Gets the destination for the directions.
     */
    public: virtual GLatLng getDestination() = 0;

    /**
     * Gets travelMode
     */
    public: virtual int32 getTravelMode() = 0;

    /**
     * Gets Eta timestamp.
     */
    public: virtual int64 getEtaTs() = 0;

    /**
     * Gets the Eta.
     */
    public: virtual int64 getEta() = 0;

    /**
     * Gets the directions track.
     */
    public: virtual GTrack getTrack() = 0;
};
    
/*C*/typedef O< IDirections > GDirections;/**/
    
}

#endif // !IDIRECTIONS_H__GLYMPSE__
