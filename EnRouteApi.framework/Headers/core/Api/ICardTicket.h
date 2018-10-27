//------------------------------------------------------------------------------
//
// Copyright (c) 2016 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ICARDTICKET_H__GLYMPSE__
#define ICARDTICKET_H__GLYMPSE__

namespace Glympse
{

/*C*/
struct ICardMember;
typedef O< ICardMember > GCardMember;
/**/

/**
 * Wraps sharing or request ticket card properties.
 */
/*O*public**/ struct ICardTicket : public ICommon
{
    /**
     * @return Invite aspect. See GC::INVITE_ASPECT_*
     */
    public: virtual int32 getAspect() = 0;

    /**
     * @return Ticket with location points or request template.
     */
    public: virtual GTicket getTicket() = 0;
    
    /**
     * @return ID of the ticket shared to the card.
     */
    public: virtual GString getTicketId() = 0;

    /**
     * @return Invite code
     */
    public: virtual GString getInviteCode() = 0;

    /**
     * Returns list of card members that this card ticket is targetted toward. If null or empty then the
     * ticket is targetted to all members.
     *
     * @return List of members targetted by this Card Ticket.
     */
    public: virtual GArray<GCardMemberDescriptor>::ptr getCardMembers() = 0;

    /**
     * @return Reference code if this ticket was created in response to a request.
     */
    public: virtual GString getReference() = 0;

    /**
     * Get the card ID that this ticket belongs to.
     *
     * @return Card ID that the ticket belongs to.
     */
    public: virtual GString getCardId() = 0;
    
    /**
     * Get the card member ID that this ticket belongs to.
     *
     * @return Card member ID that the ticket belongs to.
     */
    public: virtual GString getCardMemberId() = 0;
    
    /**
     * @return Ticket creation time in milliseconds, UTC.
     */
    public: virtual int64 getCreatedTime() = 0;
};

/*C*/typedef O< ICardTicket > GCardTicket;/**/
        
}

#endif // !ICARDTICKET_H__GLYMPSE__
