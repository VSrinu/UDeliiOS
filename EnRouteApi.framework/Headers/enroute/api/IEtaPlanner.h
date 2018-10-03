//------------------------------------------------------------------------------
//
// Copyright (c) 2015 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IETAPLANNER_H__ENROUTE__GLYMPSE__
#define IETAPLANNER_H__ENROUTE__GLYMPSE__

namespace Glympse
{
namespace EnRoute
{

/*O*public**/ struct IEtaPlanner : public ISource
{
    /**
     * @param stops Must be a GVector of GLatLng objects.
     */
    public: virtual void query(const GLatLng& start, const GVector<GCommonObj>::ptr& stops, int64 stopoverTime) = 0;
    public: virtual void abort() = 0;
    
    public: virtual void stop() = 0;
};

/*C*/typedef O<IEtaPlanner> GEtaPlanner;/**/
    
}
}

#endif // !IETAPLANNER_H__ENROUTE__GLYMPSE__