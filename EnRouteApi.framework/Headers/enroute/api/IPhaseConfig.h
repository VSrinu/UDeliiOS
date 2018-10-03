//------------------------------------------------------------------------------
//
// Copyright (c) 2015 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IPHASECONFIG_H__ENROUTE__GLYMPSE__
#define IPHASECONFIG_H__ENROUTE__GLYMPSE__

namespace Glympse
{
namespace EnRoute
{
    
/*O*public**/ struct IPhaseConfig : public ICommon
{
    /**
     * @return true, if location is visible for this phase.
     */
    public: virtual bool isVisible() = 0;
    
    /**
     * @return true, if eta should be cleared when this phase is set.
     */
    public: virtual bool shouldClearEta() = 0;
    
    /**
     * @return true, if this phase should be available in the task flow.
     */
    public: virtual bool enabledInFlow() = 0;
    
    /**
     * @return List of metadata primitives to set when this phase is applied.
     */
    public: virtual GArray<GPrimitive>::ptr getMetadata() = 0;

};

/*C*/typedef O<IPhaseConfig> GPhaseConfig;/**/
    
}
}

#endif // !IPHASECONFIG_H__ENROUTE__GLYMPSE__
