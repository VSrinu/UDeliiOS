//------------------------------------------------------------------------------
//
// Copyright (c) 2015 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IETATRIGGER_H__GLYMPSE__
#define IETATRIGGER_H__GLYMPSE__

namespace Glympse
{
    
/**
 * Extends basic trigger with the ability to act based on a given ticket's ETA value.
 */
/*O*public**/ struct IEtaTrigger : public ITrigger
{
    /**
     * Gets ticket whose ETA is being tracked by the trigger.
     */
    public: virtual GTicket getEtaTicket() = 0;
    
    /**
     * Gets trigger threshold associated with the trigger.
     */
    public: virtual int64 getThreshold() = 0;
    
    /**
     * Gets transition type monitored by the trigger. Transition type is a bitmask.
     * See CC::ETA_TRANSITION_* for more details.
     */
    public: virtual int32 getTransition() = 0;
    
};

/*C*/typedef O< IEtaTrigger > GEtaTrigger;/**/
    
}

#endif // !IETATRIGGER_H__GLYMPSE__
