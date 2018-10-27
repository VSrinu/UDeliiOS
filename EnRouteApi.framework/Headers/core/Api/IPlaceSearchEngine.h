//------------------------------------------------------------------------------
//
// Copyright (c) 2014 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IPLACESEARCHENGINE_H__GLYMPSE__
#define IPLACESEARCHENGINE_H__GLYMPSE__

namespace Glympse
{
    
/**
 * Exposes place search functionality.
 *
 * @see GlympseEvents#LISTENER_PLACE_SEARCH for the list of events fired by this component.
 *
 * @note This feature must be enabled on API key basis and is disabled by default.
 */
/*O*public**/ struct IPlaceSearchEngine : public IEventSink
{
    /**
     * Initiates search of POIs based on search term and location. 
     *
     * Multiple simultaneous searches are not currently supported.
     * Subsequent request automatically cancels previously scheduled one whithout sending any confirmation events.
     *
     * GlympseEvents#PLACE_SEARCH_COMPLETED is fired upon success even if no POIs are found. 
     * GlympseEvents#PLACE_SEARCH_FAILED indicates that search request has failed without providing a reason. 
     *
     * @param term Search query provided by the user.
     * @param location Center point of the area where search is performed.
     * @param context Arbitrary context provided by host application.
     * @return Instance of GPlaceSearchRequest object encapsulating request details.
     */
    public: virtual GPlaceSearchRequest search(const GString& term, const GLatLng& location, const GCommonObj& context) = 0;
};
    
/*C*/typedef O< IPlaceSearchEngine > GPlaceSearchEngine;/**/

}

#endif // !IPLACESEARCHENGINE_H__GLYMPSE__
