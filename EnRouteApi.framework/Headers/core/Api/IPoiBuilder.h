//------------------------------------------------------------------------------
//
// Copyright (c) 2017 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IPOIBUILDER_H__GLYMPSE__
#define IPOIBUILDER_H__GLYMPSE__

namespace Glympse
{
    
/**
 * Provides an interface for building POIs.
 */
/*O*public**/ struct IPoiBuilder : public ICommon
{
    public: virtual void setLocation(const GLatLng& location) = 0;
    
    public: virtual void setAddress(const GAddress& address) = 0;
    
    public: virtual void setName(const GString& name) = 0;
    
    public: virtual void setLabel(const GString& label) = 0;
    
    public: virtual void setProviderId(const GString& providerId) = 0;
    
    public: virtual void setExternalId(const GString& externalId) = 0;
    
    /**
     * Get the built POI from the builder. The POI may be null indicating that a name, label, or location has not been set.
     */
    public: virtual GPoi getPoi() = 0;
};

/*C*/typedef O< IPoiBuilder > GPoiBuilder;/**/
    
}

#endif // !IPOIBUILDER_H__GLYMPSE__

