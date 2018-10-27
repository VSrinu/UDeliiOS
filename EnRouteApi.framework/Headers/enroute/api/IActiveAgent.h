//------------------------------------------------------------------------------
//
// Copyright (c) 2014 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IACTIVEAGENT_H__ENROUTE__GLYMPSE__
#define IACTIVEAGENT_H__ENROUTE__GLYMPSE__

namespace Glympse
{
namespace EnRoute
{

/*O*public**/ struct IActiveAgent : public ICommon
{
    /**
     * Gets the underlying Agent.
     */
    public: virtual GAgent getAgent() = 0;

    /**
     * Gets the session associated with this active agent.
     */
    public: virtual GSession getSession() = 0;

    /**
     * Gets the underlying Agent's id.
     */
    public: virtual int64 getAgentId() = 0;
    
    /**
     * Gets the ticket associated with the underlying Agent.
     */
    public: virtual GTicket getTicket() = 0;

};

/*C*/typedef O<IActiveAgent> GActiveAgent;/**/
    
}
}

#endif // !IACTIVEAGENT_H__ENROUTE__GLYMPSE__
