//------------------------------------------------------------------------------
//
// Copyright (c) 2016 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ICARDINVITE_H__GLYMPSE__
#define ICARDINVITE_H__GLYMPSE__

namespace Glympse
{

/**
 * Exposes card invite properties.
 */
/*O*public**/ struct ICardInvite : public IEventSink
{
    /**
     * Get the time the invite was created.
     *
     * @return Invite creation time in Epoch ms.
     */
    public: virtual int64 getCreatedTime() = 0;
    
    /**
     * Get the time the invite was last modified.
     *
     * @return Invite last modified time in Epoch ms.
     */
    public: virtual int64 getLastModifiedTime() = 0;

    /**
     * @return Unique identifier for this card invite.
     */
    public: virtual GString getId() = 0;

    /**
     * @return Card ID which this invite belongs to. null if not associated to a card yet.
     */
    public: virtual GString getCardId() = 0;
    
    /**
     * @return Invite describing type of invite.
     */
    public: virtual GInvite getInvite() = 0;

    /**
     * @return Gets the card member which created the invite. null if not associated to a card yet.
     */
    public: virtual GCardMemberDescriptor getInviter() = 0;
    
    /**
     * @return Gets member who joined a card via the invite. null if not associated to a card yet.
     */
    public: virtual GCardMemberDescriptor getInvitee() = 0;
};

/*C*/typedef O< ICardInvite > GCardInvite;/**/

}

#endif // !ICARDINVITE_H__GLYMPSE__
