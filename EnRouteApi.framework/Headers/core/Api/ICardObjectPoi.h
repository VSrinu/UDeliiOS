//------------------------------------------------------------------------------
//
// Copyright (c) 2017 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ICARDOBJECTPOI_H__GLYMPSE__
#define ICARDOBJECTPOI_H__GLYMPSE__

namespace Glympse
{
    
/**
 * Interface for POI card data object.
 */
/*O*public**/ struct ICardObjectPoi : public virtual ICardObject
{
    
    /**
     * @return Base POI object wrapped by the CardObjectPoi.
     */
    public: virtual GPoi getPoi() = 0;
    
    /**
     * Allows the POI object to updated.
     */
    public: virtual void updatePoi(const GPoi& poi) = 0;

};

/*C*/typedef O< ICardObjectPoi > GCardObjectPoi;/**/
    
}

#endif // !ICARDOBJECTPOI_H__GLYMPSE__
