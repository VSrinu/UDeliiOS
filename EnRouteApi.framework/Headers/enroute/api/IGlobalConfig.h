//------------------------------------------------------------------------------
//
// Copyright (c) 2014 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IGLOBALCONFIG_H__ENROUTE__GLYMPSE__
#define IGLOBALCONFIG_H__ENROUTE__GLYMPSE__

namespace Glympse
{
namespace EnRoute
{
        
/*O*public**/ struct IGlobalConfig : public ICommon
{
    public: virtual GPrimitive asPrimitive() = 0;
    public: virtual int32 getMinSdkBuild() = 0;
};
    
/*C*/typedef O<IGlobalConfig> GGlobalConfig;/**/
    
}
}

#endif // !IGLOBALCONFIG_H__ENROUTE__GLYMPSE__
