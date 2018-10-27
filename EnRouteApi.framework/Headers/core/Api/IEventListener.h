//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IEVENTLISTENER_H__GLYMPSE__
#define IEVENTLISTENER_H__GLYMPSE__

namespace Glympse 
{
    
/*C*/
struct IGlympse;
typedef O< IGlympse > GGlympse;
/**/

/**
 * The listener interface for receiving Glympse events. Any class that implements the IEventListener interface 
 * and registers it by calling the IEventSink#addListener method will be called back with various Glympse events 
 * as they occur. When a listener is no longer needed, it should be unregistered by calling the 
 * IEventSink#removeListener method.
 */
/*O*public**/ struct IEventListener : public virtual ICommon
{
    /**
     * This method is invoked each time, when sink object notifies subscriber on an event. 
     *
     * @param glympse Glympse platform instance.
     * @param listener Listener type. See GlympseEvents for more details.
     * @param events Events bitmask. See GlympseEvents for more details.
     * @param obj Argument associated with an event. See GlympseEvents for more details.
     */
    public: virtual void eventsOccurred(const GGlympse& glympse, int32 listener, int32 events, const GCommonObj& obj) = 0;
};
    
/*C*/typedef O< IEventListener > GEventListener;/**/
    
}
    
#endif // !IEVENTLISTENER_H__GLYMPSE__
