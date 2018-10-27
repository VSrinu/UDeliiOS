//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IAPISTATUS_H__GLYMPSE__
#define IAPISTATUS_H__GLYMPSE__

namespace Glympse 
{
    
/**
 * Provides the ability to query the availability of the Glympse API services.
 */
/*O*public**/ struct IApiStatus : public ICommon
{
    /**
     * Check the status of the Glympse API services. This is a one-shot API status check
     * and only a single status request may be active at any given time. Upon API status 
     * determination, the provided listener will be notified via the statusUpdated(...) 
     * method.
     *
     * Note that each time this method is successfully invoked, a thread is spawned and 
     * one or more network operations are performed in order to determine the Glympse
     * API service status.
     *
     * @param listener The listener to be updated when the API status is determined.
     *
     * @return true, if the status request was successfully queued, false otherwise.
     */
    public: virtual bool checkStatus(const GApiStatusListener& listener) = 0;
};
    
/*C*/typedef O< IApiStatus > GApiStatus;/**/
    
}

#endif // !IAPISTATUS_H__GLYMPSE__
