//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IGROUPINVITE_H__GLYMPSE__
#define IGROUPINVITE_H__GLYMPSE__

namespace Glympse
{
    
/**
 * Incapsulates public group information and incoming invite details.
 */
/*O*public**/ struct IGroupInvite : public ICommon
{
    /**
     * Gets group name.     
     * @return Group name.
     */
    public: virtual GString getGroupName() = 0;
        
    /**
     * Gets invite object incapsulating some information on the way this group invite was received.
     * @return GInvite object or NULL.
     */
    public: virtual GInvite getInvite() = 0;
};
    
/*C*/typedef O< IGroupInvite > GGroupInvite;/**/
    
}

#endif // !IGROUPINVITE_H__GLYMPSE__
