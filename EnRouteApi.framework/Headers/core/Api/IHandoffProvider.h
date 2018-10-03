//------------------------------------------------------------------------------
//
// Copyright (c) 2013 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IHANDOFFPROVIDER_H__GLYMPSE__
#define IHANDOFFPROVIDER_H__GLYMPSE__

namespace Glympse
{
 
/**
 * The interface to abstract the details of implementation of specific handoff provider.
 */
/*O*public**/ struct IHandoffProvider : public ICommon
{
    /**
     * Indicates whether provider session is currently enabled. 
     *
     * @return true if provider is enabled.
     */
    public: virtual bool isEnabled() = 0;
    
    /**
     * Gets unique provider identifier. 
     * 
     * Currently supported providers:
     * - "gogo"
     * - "mojio"
     *
     * @return Provider identifier in a form of short lowercase string.
     */
    public: virtual GString getProviderId() = 0;
    
    /**
     * Tells host application if platform is fully functional and can handoff active tickets 
     * by means of the provider. 
     *
     * This property can be used by host applications to choose the course of action, 
     * when provider is activated. Some providers allow alternative mechanisms for sending 
     * tickets when device is not connected to the internet.
     *
     * @return true if handoff is currently available.
     * @see getActionUri
     */
    public: virtual bool isHandoffAvailable() = 0;
    
    /**
     * Indicates whether this provider is allowed to be directly set as the active handoff provider.
     *
     * @return true if the provider is forceable.
     */
    public: virtual bool isForceable() = 0;
    
    /**
     * Generates action URI for external operations supported by the provider.
     *
     * Action URI is supposed to be invoked in platform specific way to be picked up by 
     * corresponding application (in most cases - default browser) based on URI schema. 
     *
     * The most commonly used action is GC#HANDOFF_ACTION_SEND.
     *
     * @see GC#HANDOFF_ACTION_*
     */
    public: virtual GString getActionUri(int32 action) = 0;
    
    /**
     * Provides bitmask of fields that should not be disabled in the UI while provider is active.
     * The limitation is usually caused by the fact that corresponding tracking agent will override
     * those fields anyway after successful handoff.
     *
     * @return Combinatino of disabled fields.
     * @see GC#TICKET_FIELD_*
     */
    public: virtual int32 getDisabledTicketFields() = 0;
    
    /**
     * Ticket handoff procedure is aimed to enhance user experience. However some accompanying actions
     * performed by the platform go in contrast with its regular behavior. Therefore user confirmation
     * is required in order for this techniqueue to be enabled.
     *
     * The method needs to be invoked upon receiving confirmation from a user.
     *
     * Platform does not persist user preference, but it is kept in memory for the entire duration of
     * application session. Host application is free to persist user choice and apply it every time 
     * when provider is activated.
     *
     * Handoff is not allowed by default.
     */
    public: virtual void allowHandoff() = 0;
    
    /**
     * Checks to see if user has already allowed ticket handoff in this session.
     *
     * @return true if handoff is allowed in this session.
     * @see allowHandoff
     */
    public: virtual bool isHandoffAllowed() = 0;
};
    
/*C*/typedef O< IHandoffProvider > GHandoffProvider;/**/
    
}

#endif // !IHANDOFFPROVIDER_H__GLYMPSE__
