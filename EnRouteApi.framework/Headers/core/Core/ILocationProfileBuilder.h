//------------------------------------------------------------------------------
//
// Copyright (c) 2016 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ILOCATIONPROFILEBUILDER_H__GLYMPSE__
#define ILOCATIONPROFILEBUILDER_H__GLYMPSE__

namespace Glympse
{
    
/**
 * Provides an interface for building location profiles.
 */
/*O*public**/ struct ILocationProfileBuilder : public ICommon
{
    public: virtual void setMode(int32 mode) = 0;
    
    public: virtual void setSource(int32 source) = 0;
    
    public: virtual void setDistance(double distance) = 0;
    
    public: virtual void setAccuracy(double accuracy) = 0;
    
    public: virtual void setFrequency(int32 frequency) = 0;
    
    public: virtual void setPriority(int32 priority) = 0;
    
    public: virtual void setActivity(int32 activity) = 0;
    
    public: virtual void setAutoPauseEnabled(bool enabled) = 0;
    
    public: virtual void setSignificantLocationChangeMonitoringEnabled(bool enabled) = 0;
    
    public: virtual GLocationProfile getLocationProfile() = 0;
};

/*C*/typedef O< ILocationProfileBuilder > GLocationProfileBuilder;/**/

}

#endif // !ILOCATIONPROFILEBUILDER_H__GLYMPSE__

