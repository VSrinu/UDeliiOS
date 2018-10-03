//------------------------------------------------------------------------------
//
// Copyright (c) 2014 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IAGENT_H__ENROUTE__GLYMPSE__
#define IAGENT_H__ENROUTE__GLYMPSE__

namespace Glympse
{
namespace EnRoute
{
        
/*O*public**/ struct IAgent : public ICommon
{
    /**
     * Gets the primitive representation of this agent.
     */
    public: virtual GPrimitive asPrimitive() = 0;
    
    /**
     * Gets the unique id of the task.
     */
    public: virtual int64 getId() = 0;
    
    /**
     * Gets the list of roles this agent has.
     */
    public: virtual GArray<GString>::ptr getRoles() = 0;
    
    /**
     * Gets the list of tags this agent has.
     */
    public: virtual GArray<GString>::ptr getTags() = 0;
    
    /**
     * Gets the username of the Glympse user associated with this agent.
     */
    public: virtual GString getGlympseUsername() = 0;
    
    /**
     * Gets the name of this agent.
     */
    public: virtual GString getName() = 0;
    
    /**
     * Gets the email address of this agent.
     */
    public: virtual GString getEmail() = 0;
    
    /**
     * Gets the avatar of the Glympse user associated with this agent.
     */
    public: virtual GString getGlympseAvatarUrl() = 0;
};
    
/*C*/typedef O<IAgent> GAgent;/**/
    
}
}

#endif // !IAGENT_H__ENROUTE__GLYMPSE__
