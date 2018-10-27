//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IPROXIMITYLISTENER_H__GLYMPSE__
#define IPROXIMITYLISTENER_H__GLYMPSE__

namespace Glympse
{
    
/**
 * Common interface for receiving updates from proximity provider.
 */
/*O*public**/ struct IProximityListener : public virtual ICommon
{
    /**
     * Fired when region is entered.
     */
    public: virtual void regionEntered(const GRegion& region) = 0;
        
    /**
     * Fired when region is left.
     */
    public: virtual void regionLeft(const GRegion& region) = 0;
};
    
/*C*/typedef O< IProximityListener > GProximityListener;/**/
    
}

#endif // !IPROXIMITYLISTENER_H__GLYMPSE__
