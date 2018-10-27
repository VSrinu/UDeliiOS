//------------------------------------------------------------------------------
//
// Copyright (c) 2015 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IFAVORITESMANAGER_H__GLYMPSE__
#define IFAVORITESMANAGER_H__GLYMPSE__

namespace Glympse 
{

/**
 * Manager to get list of server synced favorites. When changes are made
 * to the favorites they are synced to the server.
 */
/*O*public**/ struct IFavoritesManager : public IEventSink
{  
    public: virtual void setDraft(const GTicket& draft) = 0;

    public: virtual GTicket getDraft() = 0;
    
    public: virtual GArray<GTicket>::ptr getFavorites() = 0;
    
    public: virtual void addFavorite(const GTicket& ticket) = 0;
    
    public: virtual GTicket findMatch(const GTicket& ticket) = 0;
    
    public: virtual bool hasFavorite(const GTicket& ticket) = 0;
    
    public: virtual void removeFavorite(int32 index) = 0;
    
    public: virtual void removeFavorite(const GTicket& ticket) = 0;
    
    public: virtual void moveFavorite(int32 fromIndex, int32 toIndex) = 0;    

    public: virtual void updateFavorite(const GTicket& ticket, int32 index) = 0;
};

/*C*/typedef O< IFavoritesManager > GFavoritesManager;/**/  
    
}

#endif // !IFAVORITESMANAGER_H__GLYMPSE__
