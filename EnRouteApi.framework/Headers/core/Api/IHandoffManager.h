//------------------------------------------------------------------------------
//
// Copyright (c) 2013 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IHANDOFFMANAGER_H__GLYMPSE__
#define IHANDOFFMANAGER_H__GLYMPSE__

namespace Glympse
{

/**
 * Provides access to handoff provider and sends corresponding events.
 *
 * @see GE#LISTENER_HANDOFF
 * @see IHandoffProvider
 */
/*O*public**/ struct IHandoffManager : public IEventSink
{
    /**
     * Provides access to currently active handoff provider.
     *
     * @return Instance of handoff provider or NULL.
     */
    public: virtual GHandoffProvider getHandoffProvider() = 0;
    
    /**
     * Attempts to set the matching handoff provider as the currently active handoff provider. All current and future tickets will be handed off to this provider.
     * Provider must be "forceable" and a non-forceable provider must not be currently active.
     *
     * @param providerId Handoff provider ID.
     * @param config Primitive object containing the properties specific to the handoff provider.
     */
    public: virtual bool forceHandoffProvider(const GString& providerId, const GPrimitive& data) = 0;
    
    /**
     * Disables the currently active handoff provider, if it is a forceable provider.
     */
    public: virtual bool disableHandoffProvider() = 0;
    
    /**
     * @name Debug Tools
     *
     * All methods from this section are intended for development purposes only and are not 
     * supposed to be invoked from production code.
     */
    
    /**
     * Overrides default configuration of a handoff provider.
     *
     * This method should be called before platform is started othwrise it makes no affect.
     *
     * @param providerId Handoff provider ID.
     * @param config Primitive object containing the properties to be overridden.
     */
    public: virtual void overrideProviderConfig(const GString& providerId, const GPrimitive& config) = 0;
    
};
    
/*C*/typedef O< IHandoffManager > GHandoffManager;/**/
    
}

#endif // !INETWORKMANAGER_H__GLYMPSE__
