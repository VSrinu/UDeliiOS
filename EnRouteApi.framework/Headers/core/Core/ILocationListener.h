//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ILOCATIONLISTENER_H__GLYMPSE__
#define ILOCATIONLISTENER_H__GLYMPSE__

namespace Glympse 
{
 
/**
 * Common interface for receiving updates from location provider.
 */
/*O*public**/ struct ILocationListener : public virtual ICommon
{
    /**
     * Notifies on new location.
     */
    public: virtual void locationChanged(const GLocation& location) = 0;
    
    /**
     * Location provider state changed. See CC::LOCATION_STATE_* for more details.
     *
     * This method is called by ILocationProvider.
     */
    public: virtual void stateChanged(int32 state) = 0;
};
    
/*C*/typedef O< ILocationListener > GLocationListener;/**/
    
}

#endif // !ILOCATIONLISTENER_H__GLYMPSE__
