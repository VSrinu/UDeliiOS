//------------------------------------------------------------------------------
//
// Copyright (c) 2014 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IOPERATION_H__ENROUTE__GLYMPSE__
#define IOPERATION_H__ENROUTE__GLYMPSE__

namespace Glympse
{
namespace EnRoute
{

/*O*public**/ struct IOperation : public ICommon
{
    /**
     * Gets the state of the operation. See EnRouteConstants for possible operation states.
     */
    public: virtual int32 getState() = 0;    
    
    /**
     * Gets the unique id for this operation.
     */
    public: virtual int64 getId() = 0;
    
    /**
     * Gets the start time for this operation.
     */
    public: virtual int64 getStartTime() = 0;
    
    /**
     * Gets the id of the ticket associated with this operation.
     */
    public: virtual GString getTicketId() = 0;
    
    /**
     * Gets the invite url associated with this operation.
     */
    public: virtual GString getInviteUrl() = 0;
    
    /**
     * Gets the invite code associated with this operation.
     */
    public: virtual GString getInviteCode() = 0;
    
    /**
     * Gets the task ID associated with this operation.
     */
    public: virtual int64 getTaskId() = 0;
    
    /**
     * Gets the ticket associated with this operation.
     */
    public: virtual GTicket getTicket() = 0;
    
    /**
     * Sets the eta for the ticket associated with this operation.
     */
    public: virtual void setTicketEta(int64 eta) = 0;
    
    /**
     * Sets the visibility of this operation's ticket. This allows or disallows the recipient
     * to see live updates.
     */
    public: virtual void setTicketVisibile(bool visible) = 0;
    
    /**
     * Checks whether or not the ticket is currently visible.
     */
    public: virtual bool isTicketVisible() = 0;
    
    /**
     * Appends data to the ticket associated with this operation.
     */
    public: virtual void applyTicketMetadata(const GArray<GPrimitive>::ptr& metadata) = 0;
};
    
/*C*/typedef O<IOperation> GOperation;/**/
        
}
}

#endif // !IOPERATION_H__ENROUTE__GLYMPSE__
