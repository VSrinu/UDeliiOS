//------------------------------------------------------------------------------
//
// Copyright (c) 2015 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ITASKMANAGER_H__ENROUTE__GLYMPSE__
#define ITASKMANAGER_H__ENROUTE__GLYMPSE__

namespace Glympse
{
namespace EnRoute
{
        
/*O*public**/ struct ITaskManager : public ISource
{
    /**
     * Refreshes task data. This method is not necessary to call if the app receives PUSH notifications
     * that let it know when new data is available.
     */
    public: virtual void refresh() = 0;
    
    /**
     * Gets the list of all tasks.
     */
    public: virtual GArray<GTask>::ptr getTasks() = 0;
    
    /**
     * Gets the list of pending tasks.
     */
    public: virtual GArray<GTask>::ptr getPendingTasks() = 0;
    
    /**
     * Gets the list of active operations.
     */
    public: virtual GArray<GOperation>::ptr getActiveOperations() = 0;
    
    /**
     * Look up a task using its ID
     */
    public: virtual GTask findTaskById(int64 id) = 0;
    
    /**
     * Look up an operation using a GTicket belonging to that operation.
     */
    public: virtual GOperation findOperationByTicket(const GTicket& ticket) = 0;
    
    /**
     * Starts the given task using the default duration
     */
    public: virtual bool startTask(const GTask& task) = 0;
    
    /**
     * Starts the given task using the specified duration.
     */
    public: virtual bool startTask(const GTask& task, int32 duration) = 0;
    
    /**
     * Changes the phase of the given task.
     *
     * @param task The task to change
     * @param phase The new phase to change the operation to. See EnRouteConstants for possible phase properties.
     */
    public: virtual bool setTaskPhase(const GTask& task, const GString& phase) = 0;
    
    /**
     * Completes the given operation.
     */
    public: virtual bool completeOperation(const GOperation& operation) = 0;
};
    
/*C*/typedef O<ITaskManager> GTaskManager;/**/
    
}
}

#endif // !ITASKMANAGER_H__ENROUTE__GLYMPSE__
