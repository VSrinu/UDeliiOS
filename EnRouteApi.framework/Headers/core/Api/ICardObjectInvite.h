//------------------------------------------------------------------------------
//
// Copyright (c) 2017 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ICARDOBJECTINVITE_H__GLYMPSE__
#define ICARDOBJECTINVITE_H__GLYMPSE__

namespace Glympse
{
    
/**
 * Interface for POI card data object.
 */
/*O*public**/ struct ICardObjectInvite : public virtual ICardObject
{
    
    /**
     * @return Base invite code wrapped by the CardObjectInvite.
     */
    public: virtual GString getInviteCode() = 0;
    
};

/*C*/typedef O< ICardObjectInvite > GCardObjectInvite;/**/
    
}

#endif // !ICARDOBJECTINVITE_H__GLYMPSE__
