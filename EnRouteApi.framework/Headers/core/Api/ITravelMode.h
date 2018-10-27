//------------------------------------------------------------------------------
//
// Copyright (c) 2013 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ITRAVELMODE_H__GLYMPSE__
#define ITRAVELMODE_H__GLYMPSE__

namespace Glympse
{
    
/** 
 * Provides information about the way user is travelling (walking, running, driving, etc.).
 */
/*O*public**/ struct ITravelMode : public IComparable, public IPersistable
{
    /**
     * Gets travel mode.
     *
     * @return Travel mode choosen by user.
     * @see GC#TRAVEL_MODE_*
     */
    public: virtual int32 getMode() = 0;
    
    /**
     * Gets blob of settings associated with specific travel mode.
     *
     * @return The blob of travel mode specific settings or NULL.
     */
    public: virtual GPrimitive getSettings() = 0;
};
    
/*C*/typedef O< ITravelMode > GTravelMode;/**/
    
}

#endif // !ITRAVELMODE_H__GLYMPSE__
