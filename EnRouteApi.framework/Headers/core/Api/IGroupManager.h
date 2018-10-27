//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IGROUPMANAGER_H__GLYMPSE__
#define IGROUPMANAGER_H__GLYMPSE__

namespace Glympse 
{

/**
 * Contains a collection of Group objects.
 *
 * Active groups are currently tracked by the user. Glympse API only queries details
 * of active groups to minimize bandwidth and achieve best performance. Platform still
 * queries some basic data for all groups to present activity alerts even for not 
 * active groups. Note that this concept has nothing to do with user participation 
 * in those groups. 
 *
 * @see IGroup
 * @see IGroupMember
 * @see IUser  
 * @see ITicket 
 */
/*O*public**/ struct IGroupManager : public IEventSink
{
    /**
     * Determines whether or not the state of all public groups to which the user
     * belongs has beeen synchronized with the server. Upon completion, the GroupManager also 
     * sends the GE::GROUPS_SYNCED_WITH_SERVER event.
     *
     * @return true, if the state of all public groups has finished syncing.
     */
    public: virtual bool isSynced() = 0;

    /**
     * Checks group name for correctness. 
     *
     * See validateGroupName() for the list of rules applied to group names. 
     *
     * @return true, if valid group name is specified. 
     */
    public: virtual bool isValidGroup(const GString& name) = 0;
    
    /**
     * Checks group name for correctness.
     *
     * The following rules are applied to group names:
     * - Letters and digits are allowed.
     * - Group name can start with either '!' or '#' symbol.
     * - Group names do not support spaces.
     * - Special characters like “!, #, $, %, ^, &, *, +, .” are not allowed.
     * - The only allowed symbol is underscore (‘_’).
     * - Group names cannot consist of just digits. At least single letter is required.
     * - Group name length is limited to 256 characters.
     * - Group names are case insensitive.
     *
     * @return One of GC::GROUP_NAME_* values is returned. 
     */
    public: virtual int32 validateGroupName(const GString& name) = 0;
    
    /**
     * Starts viewing public group with specified name.
     *
     * @param name Group name.
     */
    public: virtual GGroup viewGroup(const GString& name) = 0;
    
    /**
     * Returns the group list collection as an array of IGroup objects.
     */    
    public: virtual GArray<GGroup>::ptr getGroups() = 0;        
    
    /**
     * Gets the Group object that matches the given group ID.
     *
     * @param groupId Group ID of the ticket you would like to find.
     * @return The Group object that matches the given group ID, or NULL if the group ID was not found.
     */ 
    public: virtual GGroup findGroupByGroupId(const GString& groupId) = 0;
    
    /**
     * @return true, if there are any initialized groups on the system.
     * The method ignores the first group, which is formed by standalone users. 
     */    
    public: virtual bool anyActive() = 0;        
    
    /**
     * Returns the active group list collection as an array of IGroup objects.
     */    
    public: virtual GEnumeration<GGroup>::ptr getTracking() = 0;
    
    /**
     * Marks specific group as active. 
     */ 
    public: virtual int32 startTracking(const GGroup& group) = 0;
    
    /**
     * Marks specific group as not active. 
     */ 
    public: virtual int32 stopTracking(const GGroup& group) = 0;
    
    /**
     * Activate all groups on the list. This tool is useful for displaying
     * "World View" with all active tickets in a single place. It is required to 
     * decode all groups for this purpose. 
     */ 
    public: virtual void startTrackingAll() = 0;
    
    /**
     * Deactivate all groups on the list. This tool should be used, when 
     * user returns to the list of groups. So none of them is active any more. 
     */
    public: virtual void stopTrackingAll(bool forced) = 0;
    
    /**
     * @return true, if there are any initialized groups tracked by user on the system.
     * The method ignores the first group, which is formed by standalone users. 
     */
    public: virtual bool anyActiveTracked() = 0;
    
    /**
     * @return true, if group is being tracked.
     */
    public: virtual bool isTracking(const GGroup& group) = 0;
};
    
/*C*/typedef O< IGroupManager > GGroupManager;/**/
    
}

#endif // !IGROUPMANAGER_H__GLYMPSE__
