//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef INETWORKMANAGER_H__GLYMPSE__
#define INETWORKMANAGER_H__GLYMPSE__

namespace Glympse 
{
 
/**
 * Exposes some basic realtime information on the availability of Glympse REST API server
 * and provides a way for subscribing on low-level network related events.
 */
/*O*public**/ struct INetworkManager : public IEventSink
{
    /**
     * Checks whether any data has been received from Glympse server during this session.
     */
    public: virtual bool isInitialDataReceived() = 0;
    
    /**
     * Checks to see if platform is currently failing to talk to Glympse server.
     */ 
    public: virtual bool isNetworkError() = 0;
    
    /**
     * Returns availability of push notifications.
     */
    public: virtual int32 getPushAvailability() = 0;
    
    /**
     * Issues free form HTTP request.
     *
     * GE#NETWORK_RESPONSE_RECEIVED event is fired upon request completion.
     *
     * @note No one should modify request object after this call is made.
     *
     * @param request Request object.
     * @return true, if request is scheduled successfully.
     */
    public: virtual bool issueHttpRequest(const GPrimitive& request) = 0;
};
    
/*C*/typedef O< INetworkManager > GNetworkManager;/**/
    
}

#endif // !INETWORKMANAGER_H__GLYMPSE__
