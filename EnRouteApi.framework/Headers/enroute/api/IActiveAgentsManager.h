//------------------------------------------------------------------------------
//
// Copyright (c) 2016 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IACTIVEAGENTSMANAGER_H__ENROUTE__GLYMPSE__
#define IACTIVEAGENTSMANAGER_H__ENROUTE__GLYMPSE__

namespace Glympse
{
namespace EnRoute
{

/*O*public**/ struct IActiveAgentsManager : public ISource
{
    /**
     * Checks to see if the Active Agents Manager has been started.
     */
    public: virtual bool isStarted() = 0;

    /**
     * Refreshes the Active Agents Manager's data from the server. It is not necessary
     * to call this method if the application is setup to receive PUSH notifications.
     */
    public: virtual void refresh() = 0;
    
    /**
     * Gets the list of active agents.
     */
    public: virtual GArray<GActiveAgent>::ptr getActiveAgents() = 0;
    
    /**
     * Looks up an agent from the list of active agents by their ID.
     */
    public: virtual GActiveAgent findActiveAgentByAgentId(int64 agentId) = 0;
    
    /**
     * Checks to see if the given Agent has an invite code and decodes it.
     */
    public: virtual void registerActiveAgent(const GActiveAgent& activeAgent) = 0;
    
    /**
     * Gets the user associated with the given agent and starts tracking them.
     */
    public: virtual void startTracking(const GActiveAgent& activeAgent) = 0;
    
    /**
     * Gets the user associated with the given agent and stops tracking them.
     */
    public: virtual void stopTracking(const GActiveAgent& activeAgent) = 0;

};

/*C*/typedef O<IActiveAgentsManager> GActiveAgentsManager;/**/

}
}

#endif // !IACTIVEAGENTSMANAGER_H__ENROUTE__GLYMPSE__
