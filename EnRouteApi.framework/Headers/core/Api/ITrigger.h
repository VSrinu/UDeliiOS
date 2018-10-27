//------------------------------------------------------------------------------
//
// Copyright (c) 2014 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ITRIGGER_H__GLYMPSE__
#define ITRIGGER_H__GLYMPSE__

namespace Glympse
{
    
/**
 * Generic trigger interface exposing basic trigger properties.
 */
/*O*public**/ struct ITrigger : public IPersistable
{
    /**
     * Gets unique trigger identifier.
     */
    public: virtual GString getId() = 0;
    
    /**
     * Gets human-friendly trigger name.
     */
    public: virtual GString getName() = 0;
    
    /**
     * Gets trigger type. 
     * See GC::TRIGGER_TYPE_* for details.
     */
    public: virtual int32 getType() = 0;
    
    /**
     * Gets time constraint applied to the trigger.
     */
    public: virtual GTimeConstraint getTimeConstraint() = 0;
    
    /**
     * Gets auto send flag telling trigger manager whether action associated
     * with the trigger should be performed automatically or confirmed with user.
     */
    public: virtual bool autoSend() = 0;
    
    /**
     * Gets ticket object associated with the trigger.
     */
    public: virtual GTicket getTicket() = 0;
};
    
/*C*/typedef O< ITrigger > GTrigger;/**/
    
}

#endif // !ITRIGGER_H__GLYMPSE__
