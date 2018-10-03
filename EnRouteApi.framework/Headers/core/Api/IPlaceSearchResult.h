//------------------------------------------------------------------------------
//
// Copyright (c) 2014 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IPLACESEARCHRESULT_H__GLYMPSE__
#define IPLACESEARCHRESULT_H__GLYMPSE__

namespace Glympse 
{

/**
 * Encapsulates properties of a single place search result.
 */
/*O*public**/ struct IPlaceSearchResult : public ICommon
{
    /**
     * Gets place location.
     */
    public: virtual GLatLng getLocation() = 0;

    /**
     * Gets place name.
     */
    public: virtual GString getName() = 0;
    
    /**
     * Gets place address.
     */
    public: virtual GString getAddress() = 0;
    
    /**
     * Gets place web site URL.
     */
    public: virtual GString getUrl() = 0;
    
    /**
     * Gets place icon (preview).
     */
    public: virtual GImage getIcon() = 0;
    
    /**
     * Gets the list of phone number types.
     */
    public: virtual GArray<GString>::ptr getPhoneNumberTypes() = 0;

    /**
     * Gets the list of phone numbers.
     */
    public: virtual GArray<GString>::ptr getPhoneNumbers() = 0;
};
    
/*C*/typedef O< IPlaceSearchResult > GPlaceSearchResult;/**/
    
}

#endif // !IPLACESEARCHRESULT_H__GLYMPSE__
