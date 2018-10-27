//------------------------------------------------------------------------------
//
// Copyright (c) 2015 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ICARDTICKETBUILDER_H__GLYMPSE__
#define ICARDTICKETBUILDER_H__GLYMPSE__

namespace Glympse
{

/**
 * The interface to construct and initialize card ticket objects.
 */
/*O*public**/ struct ICardTicketBuilder : public virtual ICommon
{
    /**
     * Sets the location or request ticket to back this card ticket.
     * 
     * @param Ticket that has location points or request template.
     */
    public: virtual void setTicket(const GTicket& ticket) = 0;

    /**
     * Add a card member to this card ticket. Adding any card members will cause the card ticket to be targetted
     * just towards those members.
     * 
     * @param member to target with this card ticket.
     */
    public: virtual void addCardMember(const GCardMember& member) = 0;

    /**
     * Sets the reference code for this card ticket. Normally only used when creating a card ticket in response to a
     * request.
     * 
     * @param Reference invite code to be set.
     */
    public: virtual void setReference(const GString& reference) = 0;

    /**
     * @return Get the final card ticket that was constructed.
     */
    public: virtual GCardTicket getCardTicket() = 0;
};

/*C*/typedef O< ICardTicketBuilder > GCardTicketBuilder;/**/
        
}

#endif // !ICARDTICKETBUILDER_H__GLYMPSE__
