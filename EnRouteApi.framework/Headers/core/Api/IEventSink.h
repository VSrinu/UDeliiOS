//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IEVENTSINK_H__GLYMPSE__
#define IEVENTSINK_H__GLYMPSE__

namespace Glympse 
{
        
/*C*/
struct IEventSink;
typedef O< IEventSink > GEventSink;
/**/
    
/**
 * Any class should implement this interface to be capable of spreading events to subscribers.
 * Each subscriber should implement IEventListener interface. 
 *
 * IEventSink also provides a chance to associate user data (context) with an object. 
 * Host applications should use key values from range [GC::CONTEXT_KEY_MIN, GC::CONTEXT_KEY_MAX].
 */
/*O*public**/ struct IEventSink : public IEventListener
{
    /**
     * Registeres event listener on the sink. It is not allowed to register 
     * the same listener multiple times. 
     */
    public: virtual bool addListener(const GEventListener& eventListener) = 0;
    
    /**
     * Unsubscribes listener from events coming from this sink. 
     */ 
    public: virtual bool removeListener(const GEventListener& eventListener) = 0;
    
    /**
     * Provides access to the collection of current listeners.
     * It is not required to check, whether listener is already on the list
     * before adding it via addListener. addListener performs this check itself. 
     */
    public: virtual GArray<GEventListener>::ptr getListeners() = 0;
    
    /**
     * Checks, where user context identified by key is already associated with the object.
     */ 
    public: virtual bool hasContext(int64 key) = 0;

    /**
     * Associates specific context (user data) with the sink. 
     * The association is only valid during object life time and is never persisted by Glympse API. 
     */
    public: virtual void associateContext(int64 key, const GCommonObj& value) = 0;
    
    /**
     * Returns context associated with the sink, or NULL, if it is not found. 
     */
    public: virtual GCommonObj getContext(int64 key) = 0;
    
    /**
     * Clears context identified by key argument.
     */ 
    public: virtual void clearContext(int64 key) = 0;
    
    /**
     * Gets enumeration of all context keys associated with the sink.
     */
    public: virtual GEnumeration<GLong>::ptr getContextKeys() = 0;
    
    /**
     * Derives context from another sink object.
     */ 
    public: virtual void deriveContext(const GEventSink& sink) = 0;
};
    
}

#endif // !IEVENTLISTENER_H__GLYMPSE__
