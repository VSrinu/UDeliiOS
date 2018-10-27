//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IAPPPROFILE_H__GLYMPSE__
#define IAPPPROFILE_H__GLYMPSE__

namespace Glympse 
{
   
/**
 * Provides information about an application.
 */
/*O*public**/ struct IAppProfile : public IComparable, public IPersistable
{
    /**
     * Gets unique application IDs. Application ID is lower case, underscore separated string.
     *
     * @return ID of the application or NULL.
     */
    public: virtual GString getId() = 0;
    
    /**
     * Gets the name of the application.
     *
     * @return The name of the application or NULL.
     */
    public: virtual GString getName() = 0;

    /**
     * Gets the application icon. This method never returns NULL. If no application icon exists, the returned image
     * will be empty.
     *
     * @return The application icon image.
     */
    public: virtual GImage getIcon() = 0;
};
    
/*C*/typedef O< IAppProfile > GAppProfile;/**/
    
}

#endif // !IAPPPROFILE_H__GLYMPSE__
