//------------------------------------------------------------------------------
//
// Copyright (c) 2014 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IGEOTRIGGER_H__GLYMPSE__
#define IGEOTRIGGER_H__GLYMPSE__

namespace Glympse
{
    
/**
 * Extends basic trigger with the ability to act upon geofencing events.
 */
/*O*public**/ struct IGeoTrigger : public ITrigger
{
    /**
     * Gets region (center and radius) associated with the trigger. 
     */
    public: virtual GRegion getRegion() = 0;
    
    /**
     * Gets transition type monitored by the trigger. Transition type is a bitmask. 
     * See CC::GEOFENCE_TRANSITION_* for more details.
     */
    public: virtual int32 getTransition() = 0;
};
    
/*C*/typedef O< IGeoTrigger > GGeoTrigger;/**/
    
}

#endif // !IGEOTRIGGER_H__GLYMPSE__
