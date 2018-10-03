//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IGROUPMEMBER_H__GLYMPSE__
#define IGROUPMEMBER_H__GLYMPSE__

namespace Glympse 
{
    
/**
 * Represents group member - authenticated user on a group.
 */
/*O*public**/ struct IGroupMember : public IUserTicket
{
};
    
/*C*/typedef O< IGroupMember > GGroupMember;/**/
    
}

#endif // !IGROUPMEMBER_H__GLYMPSE__
