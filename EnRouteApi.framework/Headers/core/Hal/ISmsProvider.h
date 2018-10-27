//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ISMSPROVIDER_H__GLYMPSE__
#define ISMSPROVIDER_H__GLYMPSE__

namespace Glympse 
{

/**
 * Provides access to generic SMS auto-send functionality. 
 *
 * Current implementation of SMS provider is not thread safe. 
 * It is only allowed to invoke sendSMS method from main application thread.  
 */ 
/*O*public**/ struct ISmsProvider : public ICommon
{    
    /**
     * This method should be used to determine, whether SMS functionality 
     * is available on specific devide at the moment.
     *
     * Currently returns GC::SMS_SEND_AUTO on iOS 4.x and 5.x, which means that all
     * SMS messages are sent in autimatic mode. No UI is presented and no 
     * additional programmatic handling on application side is required.
     *
     * Returns GC::SMS_SEND_NOT_SUPPORTED, if the feature is temporarily or
     * permanently (iPod, iPad, iOS 6.0 or above) unavailable. 
     *
     * See GlympseConstants for more details. 
     */
    public: virtual int32 canDeviceSendSms() = 0;

    /**
     * Sends SMS message. 
     *
     * Queuing SMS delivery requests is supported. Messages are sent in the 
     * order of appending to the queue. 
     *
     * @param address Recipient phone number. 
     * @param message Message body. 
     * @param listener Reference to an object implementing ISmsListener interface. 
     * @return Returns true, if SMS message is scheduled for delivery. false is returned
     * if one of method arguments (address or message) is incorrect. 
     */ 
    public: virtual bool sendSms(const GString& address, const GString& message, const GSmsListener& listener) = 0;
};  
    
/*C*/typedef O< ISmsProvider > GSmsProvider;/**/
    
}

#endif // !ISMSPROVIDER_H__GLYMPSE__
