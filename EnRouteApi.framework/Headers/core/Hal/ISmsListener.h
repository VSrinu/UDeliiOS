//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ISMSLISTENER_H__GLYMPSE__
#define ISMSLISTENER_H__GLYMPSE__

namespace Glympse 
{
    
/**
 * Provides client application with a chance to be notified on the status of SMS delivery. 
 */
/*O*public**/ struct ISmsListener : public ICommon
{    
    /**
     * Notifies client application on SMS send status. 
     *
     * Negative result does not necessarily mean that SMS functionality is broken.
     * It makes sense to retry SMS send, if it fails once. 
     *
     * @param success Indicates, whether SMS message was sent or not. 
     * @param code Reserved for internal use. 
     * @param result Reserved for internal use. 
     * @param data Reserved for internal use. 
     */ 
    public: virtual void complete(bool success, int32 code, const GString& result, const GCommon& data) = 0;
    
    /**
     * This method is invoked, when critical error occures during SMS delivery. 
     * In most cases it does not make sense to retry SMS sending using ISmsProvider any more.
     *
     * Client applications should implement this method to initiate fallback mechanism
     * instead of SMS provider. 
     */ 
    public: virtual void serviceNoLongerAvailable() = 0;
};  
    
/*C*/typedef O< ISmsListener > GSmsListener;/**/
    
}

#endif // !ISMSLISTENER_H__GLYMPSE__
