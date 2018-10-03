//------------------------------------------------------------------------------
//
// Copyright (c) 2014 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ITIMECONSTRAINT_H__GLYMPSE__
#define ITIMECONSTRAINT_H__GLYMPSE__

namespace Glympse
{
    
/**
 * Basic primitive for applying timeframe limitations to various events.
 */
/*O*public**/ struct ITimeConstraint : public IPersistable
{
    /**
     * Checks whether specified time conforms to the contraint.
     *
     * @param UTC time in milliseconds.
     * @return true if the condition is met.
     */
    public: virtual bool validate(int64 time) = 0;
    
    /**
     * Checks whether current time conforms to the contraint.
     *
     * @return true if the condition is met.
     */
    public: virtual bool validate() = 0;
};
    
/*C*/typedef O< ITimeConstraint > GTimeConstraint;/**/
    
}

#endif // !ITIMECONSTRAINT_H__GLYMPSE__
