//------------------------------------------------------------------------------
//
// Copyright (c) 2015 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ILISTENER_H__GLYMPSE__
#define ILISTENER_H__GLYMPSE__

namespace Glympse
{
    
/*C*/
struct ISource;
typedef O< ISource > GSource;
/**/

/*O*public**/ struct IListener : public virtual ICommon
{
    /**
     * This method is invoked each time, when sink object notifies subscriber on an event.
     *
     * @param source Instance of ISource producing the event.
     * @param listener Listener type.
     * @param events Events bitmask.
     * @param param1 1st argument associated with the event.
     * @param param2 2nd argument associated with the event.
     */
    public: virtual void eventsOccurred(const GSource& source, int32 listener, int32 events, const GCommonObj& param1, const GCommonObj& param2) = 0;
};

/*C*/typedef O< IListener > GListener;/**/
    
}

#endif // !ILISTENER_H__GLYMPSE__
