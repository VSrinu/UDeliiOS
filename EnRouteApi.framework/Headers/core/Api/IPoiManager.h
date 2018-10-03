//------------------------------------------------------------------------------
//
// Copyright (c) 2017 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IPOIMANAGER_H__GLYMPSE__
#define IPOIMANAGER_H__GLYMPSE__

namespace Glympse
{
    
/*O*public**/ struct IPoiManager : public IEventSink
{
    /**
     * Determine if the PoiManager is synced with the server.
     *
     * @return True if the PoiManager has synced with the server.
     */
    public: virtual bool isSynced() = 0;
    
    /**
     * Gets the list of POIs.
     *
     * @return List of POIs on the system.
     */
    public: virtual GArray<GPoi>::ptr getPois() = 0;
    
    /**
     * Add a POI locally and on the server.
     *
     * @param poi The POI to add.
     */
    public: virtual void addPoi(const GPoi& poi) = 0;
    
    /**
     * Update a currently registered POI with the values from an existing POI. All values in target POI are overwritten
     * by values from source POI, including unset values.
     *
     * @param targetPoi The POI to update.
     * @param sourcePoi The POI to use as the source of values to update on the targetPoi.
     */
    public: virtual void updatePoi(const GPoi& targetPoi, const GPoi& sourcePoi) = 0;
    
    /**
     * Remove a POI locally and on the server.
     *
     * @param poi The POI to remove.
     */
    public: virtual void removePoi(const GPoi& poi) = 0;
    
    /**
     * Get the POI corresponding to a particular id.
     *
     * @param id Id of the POI to return
     * @return The POI with the given id or NULL if not present.
     */
    public: virtual GPoi findPoiById(const GString& poiId) = 0;
};

/*C*/typedef O< IPoiManager > GPoiManager;/**/
    
}

#endif // !IPOIMANAGER_H__GLYMPSE__
