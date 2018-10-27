//------------------------------------------------------------------------------
//
// Copyright (c) 2015 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ICHRONOTRIGGER_H__GLYMPSE__
#define ICHRONOTRIGGER_H__GLYMPSE__

namespace Glympse
{
    
/**
 * Extends basic trigger with the ability to act upon timed events.
 */
/*O*public**/ struct IChronoTrigger : public ITrigger
{
    /**
     * Gets fire time associated with the trigger.
     */
    public: virtual int64 getTime() = 0;
    
};

/*C*/typedef O< IChronoTrigger > GChronoTrigger;/**/
    
}

#endif // !ICHRONOTRIGGER_H__GLYMPSE__
