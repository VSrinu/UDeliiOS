//------------------------------------------------------------------------------
//
// Copyright (c) 2014 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IORGANIZATION_H__ENROUTE__GLYMPSE__
#define IORGANIZATION_H__ENROUTE__GLYMPSE__

namespace Glympse
{
namespace EnRoute
{
        
/*O*public**/ struct IOrganization : public ICommon
{
    /**
     * Gets the primitive representation of this organization.
     */
    public: virtual GPrimitive asPrimitive() = 0;
    
    /**
     * Gets the unique id of the task.
     */
    public: virtual int64 getId() = 0;
    
    /**
     * Gets the name of the organization.
     */
    public: virtual GString getName() = 0;
    
    /**
     * Gets the email address of the organization admin.
     */
    public: virtual GString getAdminEmail() = 0;
    
    /**
     * Gets the Glympse server for this organization.
     */
    public: virtual GString getGlympseApiServer() = 0;
    
    /**
     * Gets the Glympse API key for this organization
     */
    public: virtual GString getGlympseApiKey() = 0;
    
    /**
     * Gets the list of moderators for this organization.
     */
    public: virtual GArray<GInvite>::ptr getModerators() = 0;
    
    /**
     * Gets the location of this organization's base.
     */
    public: virtual GPlace getBaseLocation() = 0;
    
    /**
     * Gets the global configuration for this organization.
     */
    public: virtual GGlobalConfig getGlobalConfig() = 0;
    
    /**
     * Gets the configuration for this organization.
     */
    public: virtual GOrgConfig getConfig() = 0;
};
    
/*C*/typedef O<IOrganization> GOrganization;/**/
        
}
}

#endif // !IORGANIZATION_H__ENROUTE__GLYMPSE__
