//------------------------------------------------------------------------------
//
// Copyright (c) 2014 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ITRIGGERSMANAGER_H__GLYMPSE__
#define ITRIGGERSMANAGER_H__GLYMPSE__

namespace Glympse
{
    
/**
 * Manages the list of triggers. Manager takes care of persisting the list
 * and listening to events causing triggers to fire (geofencing, calendar, timer).
 */
/*O*public**/ struct ITriggersManager : public IEventSink
{
    /**
     * Registers new trigger on the system.
     */
    public: virtual void addLocalTrigger(const GTrigger& trigger) = 0;
    
    /**
     * Removes trigger from the system.
     */
    public: virtual void removeLocalTrigger(const GTrigger& trigger) = 0;
    
    /**
     * Returns the list of triggers currently registered on the system.
     */
    public: virtual GArray<GTrigger>::ptr getLocalTriggers() = 0;
};
    
/*C*/typedef O< ITriggersManager > GTriggersManager;/**/
    
}

#endif // !ITRIGGERSMANAGER_H__GLYMPSE__
