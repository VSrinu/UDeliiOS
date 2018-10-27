//------------------------------------------------------------------------------
//
// Copyright (c) 2017 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ICARDOBJECT_H__GLYMPSE__
#define ICARDOBJECT_H__GLYMPSE__

namespace Glympse
{

/**
 * Base interface for data object associated with a Card.
 */
/*O*public**/ struct ICardObject : public ICommon
{
    /**
     * @return GPrimitive representing the raw data that defines this object.
     */
    public: virtual GPrimitive getData() = 0;
    
    /**
     * @return Unique ID assigned to this object.
     */
    public: virtual GString getId() = 0;
    
    /**
     * @return Type identifying this object. See CoreConstants::CARD_OBJECT_TYPE_* for more info.
     */
    public: virtual GString getType() = 0;
    
    /**
     * @return Member ID of object creator.
     */
    public: virtual GString getMemberId() = 0;
    
    /**
     * @return User ID of object owner.
     */
    public: virtual GString getUserId() = 0;
    
    /**
     * @return ID of the card this object is assocated with.
     */
    public: virtual GString getCardId() = 0;
};

/*C*/typedef O< ICardObject > GCardObject;/**/
    
}

#endif // !ICARDOBJECT_H__GLYMPSE__
