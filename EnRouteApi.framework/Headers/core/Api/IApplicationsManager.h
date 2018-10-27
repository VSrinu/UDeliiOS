//------------------------------------------------------------------------------
//
// Copyright (c) 2014 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IAPPLICATIONSMANAGER_H__GLYMPSE__
#define IAPPLICATIONSMANAGER_H__GLYMPSE__

namespace Glympse
{
    
/**
 * Exposes the list of applications that can be used to deliver Glympse invites.
 */
/*O*public**/ struct IApplicationsManager : public IEventSink
{
    /**
     * Gets the list of supported 3rd applications.
     */
    public: virtual GArray<GApplication>::ptr getApplications() = 0;
    
    /**
     * Checks if specified application is installed.
     */
    public: virtual bool isInstalled(const GApplication& application) = 0;
    
    /**
     * Checks if Glympse platform knows how to proceed with application installation.
     */
    public: virtual bool canInstall(const GApplication& application) = 0;
    
    /**
     * Initiates application installation process.
     */
    public: virtual bool install(const GApplication& application) = 0;
    
    /**
     * Determines whether application required to deliver the invite is
     * - registered on the platform and
     * - installed on the device.
     *
     * @param invite Invite object to be analyzed.
     * @return true if platform is capable of sending the invite.
     */    
    public: virtual bool canSend(const GInvite& invite) = 0;
};
    
/*C*/typedef O< IApplicationsManager > GApplicationsManager;/**/
    
}

#endif // !IAPPLICATIONSMANAGER_H__GLYMPSE__
