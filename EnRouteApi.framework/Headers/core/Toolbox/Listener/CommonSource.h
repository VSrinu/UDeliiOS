//------------------------------------------------------------------------------
//
// Copyright (c) 2015 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef COMMONSOURCE_H__GLYMPSE__
#define COMMONSOURCE_H__GLYMPSE__

namespace Glympse
{
    
/*O*public**/ class CommonSource : public Common< ISource >
{
    private: GString _source;
        
    private: GVector<GListener>::ptr _listeners;
        
    private: bool _spreading;
        
    private: GVector<GListener>::ptr _toAdd;
        
    private: GVector<GListener>::ptr _toRemove;
    
    private: GHandler _handler;
    
    public: inline CommonSource(const GString& source, const GHandler& handler)
    {
        _source = source;
        _handler = handler;
        _listeners = new Vector<GListener>();
        _spreading = false;
        _toAdd = new Vector<GListener>();
        _toRemove = new Vector<GListener>();
    }
    
    private: inline bool addListenerCore(const GListener& eventListener)
    {
        // Check whether current listener is already subscribed on source events.
        int32 hash = eventListener->hashCode();
        int32 count = _listeners->size();
        for ( int32 i = 0 ; i < count ; ++i )
        {
            GListener currentListener = _listeners->elementAt(i);
            if ( ( currentListener->hashCode() == hash ) && ( currentListener->equals(eventListener) ) )
            {
                // For now the approach is to be as stable as possible even to the detriment
                // of performance. It is should not be allowed to subscribe the same object
                // on events from the source multiple times.
                return false;
            }
        }
        
        // Add listener if it was not found.
        _listeners->addElement(eventListener);
        return true;
    }
    
    public: inline bool addListener(const GListener& eventListener)
    {
        if ( eventListener == NULL )
        {
            return false;
        }
        if ( _spreading )
        {
            _toAdd->addElement(eventListener);
            return true;
        }
        else
        {
            return addListenerCore(eventListener);
        }
    }
    
    public: inline bool removeListener(const GListener& eventListener)
    {
        if ( eventListener == NULL )
        {
            return false;
        }
        if ( _spreading )
        {
            _toRemove->addElement(eventListener);
            return true;
        }
        else
        {
            return _listeners->removeElement(eventListener);
        }
    }
    
    public: inline bool removeAllListeners()
    {
        if ( _spreading )
        {
            int32 count = _listeners->size();
            for ( int32 i = 0 ; i < count ; ++i )
            {
                GListener currentListener = _listeners->elementAt(i);
                _toRemove->addElement(currentListener);
            }
            return true;
        }
        else
        {
            _listeners->removeAllElements();
            return true;
        }
    }
    
    public: inline GArray<GListener>::ptr getListeners()
    {
        return (GArray<GListener>::ptr)_listeners;
    }
    
    public: virtual void eventsOccurredCommon(const GSource& source, int32 listener, int32 events, const GCommonObj& param1, const GCommonObj& param2)
    {
        // Skip further processing, if there are no subscribers.
        if ( _listeners->size() == 0 )
        {
            return;
        }
        
        // Check whether event occurs on main thread.
        if ( !_handler->isMainThread() )
        {
            // Reschedule event on main thread.
            _handler->post(new EventWrapper(source, listener, events, param1, param2));
            return;
        }
        
        // Check for reentrancy.
        if ( _spreading )
        {
            // Reschedule event on main thread.
            _handler->post(new EventWrapper(source, listener, events, param1, param2));
            return;
        }
        
        // Spread events on handler thread.
        eventsOccurred(source, listener, events, param1, param2);
    }
    
    public: virtual void eventsOccurred(const GSource& source, int32 listener, int32 events, const GCommonObj& param1, const GCommonObj& param2)
    {
        // Notify subscribers.
        _spreading = true;
        for ( GEnumeration<GListener>::ptr iter = _listeners->elements() ; iter->hasMoreElements() ; )
        {
            GListener eventListener = (GListener)iter->nextElement();
            try
            {
                eventListener->eventsOccurred(source, listener, events, param1, param2);
            }
            catch ( ... )
            {
            }
        }
        _spreading = false;
        
        // Perform pending registrations.
        if ( _toAdd->size() > 0 )
        {
            for ( GEnumeration<GListener>::ptr iter = _toAdd->elements() ; iter->hasMoreElements() ; )
            {
                GListener eventListener = (GListener)iter->nextElement();
                addListenerCore(eventListener);
            }
            _toAdd->removeAllElements();
        }
        
        // Perform pending cleanup.
        if ( _toRemove->size() > 0 )
        {
            for ( GEnumeration<GListener>::ptr iter = _toRemove->elements() ; iter->hasMoreElements() ; )
            {
                GListener eventListener = (GListener)iter->nextElement();
                _listeners->removeElement(eventListener);
            }
            _toRemove->removeAllElements();
        }
    }
    
    private: /*J*static**/ class EventWrapper : public Common< IRunnable >
    {
        private: GSource _source;
        
        private: int32 _listener;
        
        private: int32 _events;
        
        private: GCommonObj _param1;
        
        private: GCommonObj _param2;
        
        public: EventWrapper(const GSource& source, int32 listener, int32 events, const GCommonObj& param1, const GCommonObj& param2)
        {
            _source = source;
            _listener = listener;
            _events = events;
            _param1 = param1;
            _param2 = param2;
        }
        
        public: virtual void run()
        {
            _source->eventsOccurred(_source, _listener, _events, _param1, _param2);
        } 
    };
    
    /**
     * Static helpers
     */
    
    public: static void removeAllListeners(const GSource& source)
    {
        // NEXT: Ideally we would like to avoid cloning here. 
        GArray<GListener>::ptr listeners = source->getListeners()->clone();
        
        // Unregister listeners one by one.
        int32 count = listeners->length();
        for ( int32 index = 0 ; index < count ; ++index )
        {
            GListener listener = listeners->at(index);
            source->removeListener(listener);
        }
    }
};
    
}

#endif // !COMMONSOURCE_H__GLYMPSE__
