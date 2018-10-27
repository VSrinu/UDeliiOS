//------------------------------------------------------------------------------
//
// Copyright (c) 2015 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IAGENTMANAGER_H__ENROUTE__GLYMPSE__
#define IAGENTMANAGER_H__ENROUTE__GLYMPSE__

namespace Glympse
{
namespace EnRoute
{
    
/*O*public**/ struct IAgentManager : public ISource
{
    /**
     * Checks to see if the Agent Manager has been started.
     */
    public: virtual bool isStarted() = 0;
    
    /**
     * Refreshes the Agent Manager's data from the server. It is not necessary to call this method if the 
     * application has PUSH notifications enabled.
     */
    public: virtual void refresh() = 0;
    
    /**
     * Gets the list of Agents.
     */
    public: virtual GArray<GAgent>::ptr getAgents() = 0;
    
    /**
     * Creates a new Agent.
     */
    public: virtual void createAgent(const GString& username, const GString& name, const GString& password) = 0;
    
    /**
     * Updates the name of an existing Agent.
     */
    public: virtual void updateAgentName(const GAgent& agent, const GString& name) = 0;
    
    /**
     * Updates the password of an existing Agent.
     */
    public: virtual void updateAgentPassword(const GAgent& agent, const GString& password) = 0;
    
    /**
     * Updates the avatar of an existing Agent.
     */
    public: virtual void updateAgentAvatar(const GAgent& agent, const GDrawable& drawable) = 0;
    
    /**
     * Updates the list or roles for an existing Agent.
     */
    public: virtual void updateAgentRoles(const GAgent& agent, const GArray<GString>::ptr& roles) = 0;
    
    /**
     * Updates the list of tags for an existing Agent.
     */
    public: virtual void updateAgentTags(const GAgent& agent, const GArray<GString>::ptr& tags) = 0;
    
    /**
     * Deletes the given Agent.
     */
    public: virtual void deleteAgent(const GAgent& agent) = 0;
    
    /**
     * Submits feedback for an Agent.
     */
    public: virtual void submitAgentFeedback(const GPrimitive& feedback) = 0;
    
    /**
     * Looks up an Agent by their ID.
     */
    public: virtual GAgent findAgentById(int64 agentId) = 0;
};
    
/*C*/typedef O<IAgentManager> GAgentManager;/**/
    
}
}

#endif // !IAGENTMANAGER_H__ENROUTE__GLYMPSE__
