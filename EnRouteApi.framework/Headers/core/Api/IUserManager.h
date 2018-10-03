//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IUSERMANAGER_H__GLYMPSE__
#define IUSERMANAGER_H__GLYMPSE__

namespace Glympse 
{

/**
 * Operates with users, whos tickets are currently watched. Two major types 
 * of users can be defined:
 * - regular users;
 * - standalone users.
 *
 * Standalone users have tickets that does not belong to any group
 * (imported by means of http://glympse.com/XXX-XXX URLs). It is possible
 * that user has tickets of both types (belonging to group and not). 
 * Standalone users (returned by getStandaloneUsers()) are always a 
 * subset of regular users (returned by getUsers()).
 */
/*O*public**/ struct IUserManager : public ICommon
{
    /**
     * @name General
     *
     * Overall user management. 
     */

    /**
     * Provides a shortcut to self user.
     */
    public: virtual GUser getSelf() = 0;

    /**
     * Provides a shortcut to self track.
     */
    public: virtual GTrack getSelfTrack() = 0;
    
    /**
     * Returns the list of all users currently registered on the system.
     */
    public: virtual GArray<GUser>::ptr getUsers() = 0;
    
    /**
     * Controls whether uber collection of users (returned by getUsers()) is sorted. 
     */
    public: virtual void enableSorting(bool enable) = 0;
    
    /**
     * @name Standalone Users Manipulation
     *
     * The section provides access to standalone users.
     */
    
    /**
     * @return true, if there are any standalone users.
     */
    public: virtual bool anyActive() = 0;
    
    /**
     * Returns the list of all standalone users.
     */ 
    public: virtual GArray<GUser>::ptr getStandaloneUsers() = 0;
    
    /**
     * Specifies whether the list of standalone users should be persisted 
     * across application sessions. 
     *
     * @note Disabling this will wipe local on-disk DB, but will not
     * touch object model. All currnetly watched users will remain registered
     * on the system till library the restart. 
     * 
     * The list of standalone users is persisted locally by default.
     */
    public: virtual void enablePersistence(bool enable) = 0;
    
    /**
     * Dictates the way platform handles multiple tickets received from a user being tracked.
     *
     * Platform operates in GC#USER_TRACKING_MODE_ACTIVE mode by default.
     *
     * @param mode The mode that needs to be set.
     * @see GC#USER_TRACKING_MODE_*
     */
    public: virtual void setUserTrackingMode(int32 mode) = 0;
    
    /**
     * Gets currently set tracking mode.
     */
    public: virtual int32 getUserTrackingMode() = 0;
    
    /**
     * Start pulling updates for the user (its active standalone tickets) on regular basis.
     * The logic behind startTracking()/stopTracking() is back ended by reference conuter
     * (not a boolean flag), which allows multiple components of the same application to start
     * and stop tracking independently. 
     *
     * @return A number of components currently tracking the user (including the one that has just made the call).
     */
    public: virtual int32 startTracking(const GUser& user) = 0;
    
    /**
     * Stop pulling updates for the user. This actually decrements a counter associated
     * with particular user. Platform stops pulling updates, when the counter goes down to 0.
     *
     * @return A number of components that are still tracking the user (excluding the one 
     * that has just made the call). One of the following values can also be returned:
     * - 0 means that user manager was tracking the user before this method was invoked,
     *   and now the user is not tracked anymore.
     * - -1 means that user was not tracked even before the method was invoked.
     */
    public: virtual int32 stopTracking(const GUser& user) = 0;
    
    /**
     * Returns a number of application components that are currently tracking the user.
     * Each of such components called startTracking(GUser) or startTrackingAll(), 
     * but has not called stopTracking(GUser) or stopTrackingAll() yet.
     * In other words returned value says how many times stopTracking(GUser)
     * needs to be called in order to stop pulling updates for this user.
     *
     * @param user Standalone user object that is potentially being tracked.
     * @return One of the following values is returned:
     * - Positive integer value indicates how many components of host application
     *   are still tracking the user.
     * - -1 means that the user is not tracked at the moment.
     */
    public: virtual int32 getNumTrackers(const GUser& user) = 0;
    
    /**
     * Returns the subset of standalone users, whos information is pulled from server on regular basis.
     */
    public: virtual GEnumeration<GUser>::ptr getTracking() = 0;
    
    /**
     * Start pulling updates for all active standalone tickets currently registered on the system.
     * This method is provided for convenience. Under the covers it invokes startTracking(GUser) 
     * for each standalone user. 
     */
    public: virtual void startTrackingAll() = 0;
    
    /**
     * This method is provided for convenience. Under the covers it invokes stopTracking(GUser)
     * for each user whos updates are currently pulled from server on regular basis.
     *
     * @param forced Allows to stop all pulling updates forcibly (no matter how many times startTracking(GUser)
     * was previously called). 
     */
    public: virtual void stopTrackingAll(bool forced) = 0;
    
    /**
     * @return true, if there are any active standalone users being tracked.
     */
    public: virtual bool anyActiveTracked() = 0;
    
    /**
     * @name Lookup Tools
     *
     * Set of convenience helpers for finding users and tickets on the system.
     */
    
    /**
     * Find user by user ID or creates new user and registers it on the list.
     *
     * @param userId Glympse user identifier.
     * @return User object found on the list or newly created user.
     */
    public: virtual GUser findOrCreateUserByUserId(const GString& userId) = 0;

    /**
     * Gets the user object that matches the given user ID.
     *
     * @param userId User ID of the user you would like to find.
     * @return The user object that matches the given ID,
     * or NULL if the user was not found.
     */
    public: virtual GUser findUserByUserId(const GString& userId) = 0;

    /**
     * Gets the user object that matches the given invite code.
     * User object is not associated with any invite codes directly.
     * The lookup is made against tickets received from a user.
     *
     * @param code Invite code of the ticket you would like to find.
     * @return The user object that contains the ticket with such invite code,
     * or NULL if the ticket was not found.
     */    
    public: virtual GUser findUserByInviteCode(const GString& code) = 0;
    
    /**
     * Gets the ticket object that matches the given invite code.
     *
     * @param code Invite code of the ticket you would like to find.
     * @return The ticket object that matches the given invite code,
     * or NULL if the ticket was not found.
     */
    public: virtual GTicket findTicketByInviteCode(const GString& code) = 0;
};
    
/*C*/typedef O< IUserManager > GUserManager;/**/
    
}

#endif // !IUSERMANAGER_H__GLYMPSE__
