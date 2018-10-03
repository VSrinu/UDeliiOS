//------------------------------------------------------------------------------
//
// Copyright (c) 2014 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IAPPLICATION_H__GLYMPSE__
#define IAPPLICATION_H__GLYMPSE__

namespace Glympse
{
    
/**
 * Represents 3rd party application that can be used as a transport mechanism
 * for sending a Glympse.
 */
/*O*public**/ struct IApplication : public IAppProfile
{
    /**
     * Creates invite object that is configured to be delivered by the 3rd party application.
     *
     * @return Invite object.
     */
    public: virtual GInvite createInvite() = 0;
    
    /**
     * Determines whether specific person can be addressed withon 3rd party application.
     * People picker is usually presented by 4rd party application if no contact information
     * is specified by the caller upfront. 
     *
     * @return true if specific person can be addressed.
     */
    public: virtual bool canAddressPerson() = 0;
};
    
/*C*/typedef O< IApplication > GApplication;/**/
    
}

#endif // !IAPPLICATION_H__GLYMPSE__
