//------------------------------------------------------------------------------
//
// Copyright (c) 2017 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IPOI_H__GLYMPSE__
#define IPOI_H__GLYMPSE__

namespace Glympse
{
    
/*C*/
struct IPoi;
typedef O< IPoi > GPoi;
/**/
    
/**
 * Encapsulates a Place of Interest.
 */
/*O*public**/ struct IPoi : public ICommon
{
    /**
     * Get unique Glympse POI ID.
     */
    public: virtual GString getId() = 0;
    
    /**
     * Get the POI's physical location.
     */
    public: virtual GLatLng getLocation() = 0;
    
    /**
     * Get the POI's address.
     */
    public: virtual GAddress getAddress() = 0;
    
    /**
     * Get human readable name.
     */
    public: virtual GString getName() = 0;
    
    /**
     * Get label.
     */
    public: virtual GString getLabel() = 0;
    
    /**
     * Get Provider ID.
     */
    public: virtual GString getProviderId() = 0;
    
    /**
     * Get External ID.
     */
    public: virtual GString getExternalId() = 0;
};

}

#endif // !IPOI_H__GLYMPSE__
