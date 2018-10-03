//------------------------------------------------------------------------------
//
// Copyright (c) 2016 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ICARDMEMBER_H__GLYMPSE__
#define ICARDMEMBER_H__GLYMPSE__

namespace Glympse
{

/**
 * Exposes basic properties of a card member.
 */
/*O*public**/ struct ICardMember : public IEventSink, public virtual ICardMemberDescriptor
{
    /**
     * @return true if this member is the self member in a card.
     */
    public: virtual bool isSelf() = 0;

    /**
     * @return Information on who invited this member to the card. null if this was the first card member.
     */
    public: virtual GCardMemberDescriptor getInviter() = 0;
    
    /**
     * @return ID of the invite used to join the card or null if alternative method was used to add this member.
     */
    public: virtual GString getInviteId() = 0;

    /**
     * @return CardTicket that the member is sharing to the card. null if not currently sharing.
     */
    public: virtual GCardTicket getTicket() = 0;

    /**
     * @return CardTicket that the member is requesting to the card. null if not currently requesting.
     */
    public: virtual GCardTicket getRequest() = 0;

    /**
     * @return current card member state.
     */
    public: virtual GCardMemberState getState() = 0;

    /**
     * @return creation time Epoch(ms)
     */
    public: virtual int64 getCreatedTime() = 0;

    /**
     * @return last modified time Epoch(ms)
     */
    public: virtual int64 getLastModifiedTime() = 0;
};

/*C*/typedef O< ICardMember > GCardMember;/**/
        
}

#endif // !ICARDMEMBER_H__GLYMPSE__
