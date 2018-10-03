//------------------------------------------------------------------------------
//
// Copyright (c) 2014 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ENROUTEMANAGER_H__ENROUTE__GLYMPSE__
#define ENROUTEMANAGER_H__ENROUTE__GLYMPSE__

namespace Glympse
{
namespace EnRoute
{
    
/*O*public**/ struct IEnRouteManager : public ISource
{
    /**
     * Gets version of the sdk in the format: "{MAJOR}.{MINOR}.{BUILD}".
     *
     * MAJOR is major SDK version.
     * MINOR is minor SDK version.
     * BUILD is forever increasing SDK version number.
     *
     * Example: "2.0.41"
     */
    public: virtual GString getSdkVersion() = 0;
    
    /**
     * Registers a labeled version to be used in diagnostics. Applications and libraries using this SDK should utilize 
     * this method to register the version of their components to aid in debugging and diagnostics.
     * Label should be an all lower case, dash seperated string representing the name of the component, eg. 'technician-app'
     * Version should be of the format: "{MAJOR}.{MINOR}.{BUILD}". See 'EnRouteManager::getSdkVersion' above for more
     * information.
     */
    public: virtual void setVersion(GString label, GString version) = 0;
    
    /**
     * Allows client application to override the base url from which all api calls are based.
     * This value can only be changed before the EnRouteManager is started.
     *
     * @param baseUrl The base URL (e.g. api.enterprise.glympse.com)
     */
    public: virtual void setBaseUrl(const GString& baseUrl) = 0;
    
    /**
     * Gets the currently set baseUrl. See setBaseUrl().
     */
    public: virtual GString getBaseUrl() = 0;
    
    /**
     * Allows client application to set which authentication mode will be used. See EnRouteConstants::AUTH_MODE_* for
     * supported values. The chosen authentication mode determines which version of EnRouteManager::login() should
     * be called.
     *
     * @param mode The authentication mode in which the manager should run.
     */
    public: virtual void setAuthenticationMode(int32 mode) = 0;
    
    /**
     * Gets the currently set authentication mode. See setAuthenticationMode().
     */
    public: virtual int32 getAuthenticationMode() = 0;
    
    /**
     * Associates device PUSH handle with a given device.
     *
     * @param tokenType Push provider type.
     * @param deviceToken Push handle provided by device.
     */
    public: virtual void registerDeviceToken(const GString& tokenType, const GString& deviceToken) = 0;
    
    /**
     * Sends PUSH notification "payload" to the platform for processing.
     *
     * @param payload PUSH notification payload.
     */
    public: virtual void handleRemoteNotification(const GString& payload) = 0;
    
    /**
     * Checks to see if there is a valid token available
     *
     * @return true if there is a valid token. false if the current token is missing or expired.
     */
    public: virtual bool isLoginNeeded() = 0;
    
    /**
     * Performs a login using the provided username and password. Must be called after EnRouteManager::start()
     */
    public: virtual bool loginWithCredentials(const GString& username, const GString& password) = 0;
    
    /**
     * Performs a login using the provided access token, with the givin lifetime. Must be called after EnRouteManager::start()
     */
    public: virtual bool loginWithToken(const GString& token, int64 expireTime) = 0;
    
    /**
     * Performs a logout for the currently logged in agent. This removes the access token
     * and stops the platform after the logout completes.
     * 
     * @param reason Reason for logging out this user. See EnRouteConstants for possible values
     */
    public: virtual void logout(int32 reason) = 0;
    
    /**
     * Starts the platform when an agent has already been previously logged in.
     */
    public: virtual bool start() = 0;
    
    /**
     * Stops the platform including all sub-managers. After notifying subscribers
     * that the platform has stopped, all listeners are unregistered.
     */
    public: virtual void stop() = 0;
    
    /**
     * Checks to see if the platform has been started.
     */
    public: virtual bool isStarted() = 0;
    
    /**
     * Use this method to notify EnRoute API when the application is going to the background or returns to the
     * foreground. This method is backed by a reference count, so calls are expected to be reciprocal. When the 
     * reference count transitions from zero to one, the platform is activated; when the reference count transitions
     * from one to zero, the platform is deactivated. Note, however, that platform deactivation is not synchronous 
     * nor immediate; it is delayed for a short time in order to prevent premature deactivation in cases where it
     * will be reactivated quickly. In such cases, calls to reactivate the platform will cancel the deactivation and
     * the platform will remain active.
     *
     * @param active true, if the application has moved to the foreground, false if it has moved to the background.
     *
     * @return The active reference count. A reference count > zero means that the platform is [still] active. A 
     * reference count of zero means that the platform is, or will become, inactive.
     */
    public: virtual void setActive(bool active) = 0;
    
    /**
     * Gets platform state. 
     * 
     * @return Boolean value indicating whether platform is in active (foreground) state now. 
     */
    public: virtual bool isActive() = 0;

    /**
     * Refreshes data in sub-managers. This method is not necessary to call if the app receives PUSH notifications
     * that let it know when new data is available.
     */
    public: virtual void refresh() = 0;
    
    /**
     * Retrieves the current organization for the currently logged in agent.
     */
    public: virtual GOrganization getOrganization() = 0;
    
    /**
     * Retrieves the current user's agent.
     */
    public: virtual GAgent getSelfAgent() = 0;
    
    /**
     * Retrieves the currently logged in agent.
     * @deprecated Please user IEnRouteManager::getSelfAgent()
     */
    public: virtual GAgent getLoggedInAgent() = 0;
    
    /**
     * Retrieves the access token for the currently logged in agent.
     */
    public: virtual GString getEnRouteToken() = 0;
    
    /**
     * Gets the running instance of the Glympse platform.
     */
    public: virtual GGlympse getGlympse() = 0;
    
    /**
     * Gets the manager responsible for keeping track of tasks for the current agent.
     */
    public: virtual GTaskManager getTaskManager() = 0;
    
    /**
     * Gets the manager responsible for updating the logged in agent.
     */
    public: virtual GAgentManager getAgentManager() = 0;
    
    /**
     * Gets the list of sessions. GSessionManager is responsible for managing
     * sessions and stages via its sub-manager GStageManager.
     */
    public: virtual GSessionManager getSessionManager() = 0;

    /**
     * Gets the list of active agents that are currently tracked. GActiveAgentsManager
     * can be used to start or stop tracking agents.
     */
    public: virtual GActiveAgentsManager getActiveAgentsManager() = 0;
    
    /**
     * Gets GEtaPlanner which can be used to query for eta data.
     */
    public: virtual GEtaPlanner getEtaPlanner() = 0;
    
    /**
     * The Diagnostics collector can be used to log objects for later debugging.
     */
    public: virtual GDiagnosticsCollector getDiagnosticsCollector() = 0;
    
    /**
     * Sets Glympse's log level to the values specified. See CoreConstants for log levels
     */
    public: virtual void overrideLoggingLevels(int32 fileLogLevel, int32 debugLogLevel) = 0;
};
    
/*C*/typedef O<IEnRouteManager> GEnRouteManager;/**/
    
}
}

#endif // !ENROUTEMANAGER_H__ENROUTE__GLYMPSE__
