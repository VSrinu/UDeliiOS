//------------------------------------------------------------------------------
//
// Copyright (c) 2015 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ICARDACTIVITY_H__GLYMPSE__
#define ICARDACTIVITY_H__GLYMPSE__

namespace Glympse
{

/**
 * Exposes basic properties of card activity list.
 */
/*O*public**/ struct ICardActivity : public IEventSink
{
    /**
     * Gets the events in this list sorted from oldest to newest.
     */
    public: virtual GArray<GCardEvent>::ptr getEvents() = 0;
    
    /**
     * Gets the most recent event posted in the card.
     *
     * @return GCardEvent object or NULL if there are no events on card's activity list.
     */
    public: virtual GCardEvent getMostRecentEvent() = 0;
    
    /**
     * Gets the id of the card that this activity belongs to
     */
    public: virtual GString getCardId() = 0;

    /**
     * Determine if the activity list has completed its initial sync with the server.
     *
     * @return True if the activity list has completed initial sync with the server.
     */
    public: virtual bool isSynced() = 0;
};

/*C*/typedef O< ICardActivity > GCardActivity;/**/

}

#endif // !ICARDACTIVITY_H__GLYMPSE__
