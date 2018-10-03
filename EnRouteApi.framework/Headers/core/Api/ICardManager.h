//------------------------------------------------------------------------------
//
// Copyright (c) 2016 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ICARDMANAGER_H__GLYMPSE__
#define ICARDMANAGER_H__GLYMPSE__

namespace Glympse
{

/**
 * Main interface for manipulating Glympse Cards.
 */
/*O*public**/ struct ICardManager : public IEventSink
{
    /**
     * Get the list of cards.
     *
     * @return List of cards on the system.
     */
    public: virtual GArray<GCard>::ptr getCards() = 0;
    
    /**
     * Get the card type for the given card type ID.
     *
     * New card type is created and is registered on the list if specified ID is not found.
     *
     * @param id card type identifier
     * @return Filled in card type structure
     */
    public: virtual GCardType findCardTypeById(const GString& id) = 0;

    /**
     * Gets the list of card types.
     *
     * @return List of card types on the system.
     */
    public: virtual GArray<GCardType>::ptr getCardTypes() = 0;

    /**
     * Create a card locally and on the server. The current user will automatically be added to the card.
     *
     * @param card The card to create.
     * @return false if the card can't be added to the card list, otherwise true.
     */
    public: virtual bool createCard(const GCard& card) = 0;

    /**
     * Accept invite to joing card.
     *
     * @param card Preview of a card to be accepted.
     */
    public: virtual bool joinCard(const GCard& card) = 0;

    /**
     * Get the card corresponding to a particular id.
     *
     * @param id Id of the card to return
     * @return The card with the given id or NULL if not present.
     */
    public: virtual GCard findCardByCardId(const GString& id) = 0;
    
    /**
     * Get the member sharing ticket with given ID.
     *
     * @param ticketId Id of the ticket shared to the card.
     * @param isSelf Flag indicating whether ticket is shared by self user.
     * @return The card member or NULL if not present.
     */
    public: virtual GCardMember findCardMemberByTicketId(const GString& ticketId, bool isSelf) = 0;

    /**
     * Determine if the cardmanager is synced with the server.
     *
     * @return True if the card manager has synced with the server.
     */
    public: virtual bool isSynced() = 0;

    /**
     * Start pulling updates for the card on regular basis.
     * The logic behind startTracking()/stopTracking() is back ended by reference counter
     * (not a boolean flag), which allows multiple components of the same application to start
     * and stop tracking independently. 
     *
     * @return A number of components currently tracking the card (including the one that has just made the call).
     */
    public: virtual int32 startTracking(const GCard& card) = 0;
    
    /**
     * Stop pulling updates for the card. This actually decrements a counter associated
     * with the particular card. Platform stops pulling updates, when the counter goes down to 0.
     *
     * @return A number of components that are still tracking the card (excluding the one
     * that has just made the call). One of the following values can also be returned:
     * - 0 means that card manager was tracking the card before this method was invoked,
     *   and now the card is not tracked anymore.
     * - -1 means that card was not tracked even before the method was invoked.
     */
    public: virtual int32 stopTracking(const GCard& card) = 0;
    
    /**
     * Returns a number of application components that are currently tracking the card.
     * Each of these components called startTracking(GUser) or startTrackingAll(),
     * but has not called stopTracking(GUser) or stopTrackingAll() yet.
     * In other words returned value says how many times stopTracking(GCard)
     * needs to be called in order to stop pulling updates for this card.
     *
     * @param card Card object that is potentially being tracked.
     * @return One of the following values is returned:
     * - Positive integer value indicates how many components of host application
     *   are still tracking the card.
     * - -1 means that the card is not tracked at the moment.
     */
    public: virtual int32 getNumTrackers(const GCard& card) = 0;
    
    /**
     * Returns the subset of cards, whos information is pulled from server on regular basis.
     */
    public: virtual GEnumeration<GCard>::ptr getTracking() = 0;
    
    /**
     * @return true if any of initialized cards are being tracked.
     */
    public: virtual bool anyActiveTracked() = 0;
};
    
/*C*/typedef O< ICardManager > GCardManager;/**/

}

#endif // !ICARDMANAGER_H__GLYMPSE__
