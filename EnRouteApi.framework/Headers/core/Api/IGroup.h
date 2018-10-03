//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IGROUP_H__GLYMPSE__
#define IGROUP_H__GLYMPSE__

namespace Glympse 
{
    
/**
 * Provides access to Glympse Group object.
 */
/*O*public**/ struct IGroup : public IEventSink
{
    /**
     * @return Gets group identifier. 
     */         
    public: virtual GString getId() = 0;
    
    /**
     * @return Gets group state. See GlympseConstants for details. 
     */         
    public: virtual int32 getState() = 0;    

    /**
     * @return Gets group name or NULL if it is not set. 
     */     
    public: virtual GString getName() = 0;
    
    /**
     * @return Gets group avatar or NULL if it is not set. 
     */ 
    public: virtual GImage getAvatar() = 0;   
    
    /**
     * Array of current group members, sorted.
     */ 
    public: virtual GArray<GGroupMember>::ptr getMembers() = 0;   
    
    /**
     * Array of current group members, optionally sorted.
     */
    public: virtual GArray<GGroupMember>::ptr getMembers(bool sorted) = 0;
    
    /**
     * Array of pending invites.
     */
    public: virtual GArray<GInvite>::ptr getInvites() = 0;     
    
    /**
     * Clears the list of invites to the group.  This is used in congunction
     * with send.  Once the invites are sent, they can be cleared from the
     * array (returned from getInvites).
     */
    public: virtual void clearInvites() = 0;
    
    /**
     * Looks through the list of group members and returns member whose user id matches 
     * the value passed as an argument. 
     *
     * @param userId User identifier.
     * @return Group member object or NULL, if corresponding member is not found. 
     */ 
    public: virtual GGroupMember findMemberByUserId(const GString& userId) = 0;
    
    /**
     * Modifies current group, allowing to add/or change the name or avatar.
     * NULL value keeps corresponding property unchanged. 
     */
    public: virtual void modify(const GString& name, const GImage& avatar) = 0;
    
    /**
     * Sends group invite to new recipient.
     *
     * @param invite Invite object to be sent. 
     * @param message Optional message to be sent along with the invite. 
     * @return Returns true, if invite was scheduled to be sent. 
     */
    public: virtual bool send(const GInvite& invite, const GString& message) = 0;
    
    /**
     * Removes self user from the group. 
     */
    public: virtual void leave() = 0;
};
    
/*C*/typedef O< IGroup > GGroup;/**/
    
}

#endif // !IGROUP_H__GLYMPSE__
