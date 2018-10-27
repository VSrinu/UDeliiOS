//------------------------------------------------------------------------------
//
// Copyright (c) 2014 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IPLACESEARCHREQUEST_H__GLYMPSE__
#define IPLACESEARCHREQUEST_H__GLYMPSE__

namespace Glympse
{
 
/**
 * Object encapsulating parameters of a request.
 */
/*O*public**/ struct IPlaceSearchRequest : public ICommon
{
    /**
     * Gets search query.
     */
    public: virtual GString getSearchTerm() = 0;

    /**
     * Gets location.
     */
    public: virtual GLatLng getLocation() = 0;
    
    /**
     * Gets context specified by application when issuing the request. 
     */
    public: virtual GCommonObj getContext() = 0;
};
    
/*C*/typedef O< IPlaceSearchRequest > GPlaceSearchRequest;/**/
    
}

#endif // !IPLACESEARCHREQUEST_H__GLYMPSE__
