//------------------------------------------------------------------------------
//
// Copyright (c) 2014 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IPLACESEARCHRESULTS_H__GLYMPSE__
#define IPLACESEARCHRESULTS_H__GLYMPSE__

namespace Glympse
{

/**
 * Associates the list of place search results with the original request.
 */
/*O*public**/ struct IPlaceSearchResults : public ICommon
{
    /**
     * Gets the list of results.
     */
    public: virtual GArray<GPlaceSearchResult>::ptr getResults() = 0;
    
    /**
     * Gets original request.
     */
    public: virtual GPlaceSearchRequest getRequest() = 0;
};
    
/*C*/typedef O< IPlaceSearchResults > GPlaceSearchResults;/**/
    
}

#endif // !IPLACESEARCHRESULTS_H__GLYMPSE__
