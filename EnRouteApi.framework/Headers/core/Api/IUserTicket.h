//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IUSERTICKET_H__GLYMPSE__
#define IUSERTICKET_H__GLYMPSE__

namespace Glympse 
{
    
/**
 * Represents a combination of user and a ticket.
 */
/*O*public**/ struct IUserTicket : public ICommon
{
    /**
     * Gets user object. 
     */         
    public: virtual GUser getUser() = 0;
        
    /**
     * Gets ticket object. 
     * @return Ticket object or NULL.
     */         
    public: virtual GTicket getTicket() = 0;
    
    /**
     * Gets invite object.
     * @return Invite object or NULL.
     */
    public: virtual GInvite getInvite() = 0;
};
    
/*C*/typedef O< IUserTicket > GUserTicket;/**/
    
}

#endif // !IUSERTICKET_H__GLYMPSE__
