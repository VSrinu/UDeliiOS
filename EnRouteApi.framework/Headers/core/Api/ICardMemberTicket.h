//------------------------------------------------------------------------------
//
// Copyright (c) 2016 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ICARDMEMBERTICKET_H__GLYMPSE__
#define ICARDMEMBERTICKET_H__GLYMPSE__

namespace Glympse
{

/**
 * Convenience class to wrap a card member and card ticket.
 */
/*O*public**/ struct ICardMemberTicket : public ICommon
{
    /**
     * @return Card member object
     */
    public: virtual GCardMember getCardMember() = 0;

    /**
     * @return Card Ticket Object
     */
    public: virtual GCardTicket getCardTicket() = 0;
};

/*C*/typedef O< ICardMemberTicket > GCardMemberTicket;/**/
        
}

#endif // !ICARDMEMBERTICKET_H__GLYMPSE__
