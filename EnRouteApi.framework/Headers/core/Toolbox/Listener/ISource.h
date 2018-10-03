//------------------------------------------------------------------------------
//
// Copyright (c) 2015 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ISOURCE_H__GLYMPSE__
#define ISOURCE_H__GLYMPSE__

namespace Glympse
{
    
/**
 * Any class should implement this interface to be capable of spreading events to subscribers.
 * Each subscriber should implement IListener interface.
 *
 */
/*O*public**/ struct ISource : public IListener
{
    /**
     * Registeres event listener on the source. It is not allowed to register
     * the same listener multiple times.
     */
    public: virtual bool addListener(const GListener& eventListener) = 0;
    
    /**
     * Unsubscribes listener from events coming from this source.
     */
    public: virtual bool removeListener(const GListener& eventListener) = 0;
    
    /**
     * Provides access to the collection of current listeners.
     * It is not required to check, whether listener is already on the list
     * before adding it via addListener. addListener performs this check itself.
     */
    public: virtual GArray<GListener>::ptr getListeners() = 0;
    
};
    
}

#endif // !ISOURCE_H__GLYMPSE__
