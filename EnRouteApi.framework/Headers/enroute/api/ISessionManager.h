//------------------------------------------------------------------------------
//
// Copyright (c) 2015 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ISESSIONMANAGER_H__ENROUTE__GLYMPSE__
#define ISESSIONMANAGER_H__ENROUTE__GLYMPSE__

namespace Glympse
{
namespace EnRoute
{
    
/*O*public**/ struct ISessionManager : public ISource
{    
    /**
     * Checks whether or not the Session Manager has been started.
     */
    public: virtual bool isStarted() = 0;
    
    /**
     * Refreshes and synchronizes session data. It is not necessary to call this method
     * if the application is configured to receive PUSH notifications.
     */
    public: virtual void refresh() = 0;
    
    /**
     * Gets the list of sessions currently tracked by the Session Manager.
     */
    public: virtual GArray<GSession>::ptr getSessions() = 0;
    
    /**
     * Checks whether or not there are any sessions are in the SESSION_STATE_STARTED state.
     */
    public: virtual bool anyActiveSessions() = 0;
    
    /**
     * Starts the given session.
     */
    public: virtual void startSession(const GSession& session) = 0;
    
    /**
     * Completes the given session.
     */
    public: virtual void completeSession(const GSession& session, int32 reason) = 0;
    
    /**
     * Searches through the list of sessions for a session with the given id.
     */
    public: virtual GSession findSessionById(int64 sessionId) = 0;
    
    /**
     * @param session Session to modify
     * @param tasks Must be a GVector of GTask objects
     */
    public: virtual void updateSessionTasks(const GSession& session, const GVector<GCommonObj>::ptr& tasks) = 0;
};

/*C*/typedef O<ISessionManager> GSessionManager;/**/
    
}
}

#endif // !ISESSIONMANAGER_H__ENROUTE__GLYMPSE__
