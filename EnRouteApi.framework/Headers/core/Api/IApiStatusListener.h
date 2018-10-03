//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IAPISTATUSLISTENER_H__GLYMPSE__
#define IAPISTATUSLISTENER_H__GLYMPSE__

namespace Glympse 
{
    
/**
 * The listener interface for API status determination.
 */
/*O*public**/ struct IApiStatusListener : public virtual ICommon
{
    /**
     * This listener method is invoked after the API status is determined.
     *
     * @param available true, if the Glympse API services are available, false otherwise.
     */
    public: virtual void statusUpdated(bool available) = 0;
};
    
/*C*/typedef O< IApiStatusListener > GApiStatusListener;/**/
    
}
    
#endif // !IAPISTATUSLISTENER_H__GLYMPSE__
