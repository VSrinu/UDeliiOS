//------------------------------------------------------------------------------
//
// Copyright (c) 2014 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ITASK_H__ENROUTE__GLYMPSE__
#define ITASK_H__ENROUTE__GLYMPSE__

namespace Glympse
{
namespace EnRoute
{
        
/*O*public**/ struct ITask : public ICommon
{
    /**
     * Gets the current state of the task. See EnRouteConstants for possible task states.
     */
    public: virtual int32 getState() = 0;
    
    /**
     * Gets the unique id of the task.
     */
    public: virtual int64 getId() = 0;
    
    /**
     * Gets the parent operation this task belongs to.
     */
    public: virtual GOperation getOperation() = 0;
    
    /**
     * Gets a description of the task as a string.
     */
    public: virtual GString getDescription() = 0;
    
    /**
     * Gets the due date of the task.
     */
    public: virtual int64 getDueTime() = 0;
    
    /**
     * Gets the ticket associated with this task.
     */
    public: virtual GTicket getTicket() = 0;
    
    /**
     * Gets the phase of this task.
     */
    public: virtual GString getPhase() = 0;
    
    /**
     * Gets the foreign id associated with this Task.
     */
    public: virtual GString getForeignId() = 0;
    
    /**
     * Gets an array of metadata associated with this task.
     */
    public: virtual GArray<GPrimitive>::ptr getMetadata() = 0;
};
    
/*C*/typedef O<ITask> GTask;/**/
        
}
}

#endif // !ITASK_H__ENROUTE__GLYMPSE__
