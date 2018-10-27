//------------------------------------------------------------------------------
//
// Copyright (c) 2016 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ICARDMEMBERDESCRIPTOR_H__GLYMPSE__
#define ICARDMEMBERDESCRIPTOR_H__GLYMPSE__

namespace Glympse
{

/*C*/
struct ICard;
typedef O< ICard > GCard;
/**/

/**
 * Exposes basic properties and a state of a card.
 *
 * Host application does not create or modify card objects directly. Instead it uses methods 
 * exposed by IGlympseCards.
 */
/*O*public**/ struct ICardMemberDescriptor : public virtual ICommon
{
    /**
     * Get the unique card member identifier.
     *
     * @return Unique card member identifier.
     */
    public: virtual GString getId() = 0;

    /**
     * Get the glympse user id. Can be null if not yet a member of a card.
     *
     * @return Glympse user id.
     */
    public: virtual GString getUserId() = 0;

    /**
     * Get the card id that this member belongs to. Can be null if not yet a member of a card.
     *
     * @return card id that the member belongs to.
     */
    public: virtual GString getCardId() = 0;
};
    
/*C*/typedef O< ICardMemberDescriptor > GCardMemberDescriptor;/**/
        
}

#endif // !ICARDMEMBERDESCRIPTOR_H__GLYMPSE__
