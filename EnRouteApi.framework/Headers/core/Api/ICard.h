//------------------------------------------------------------------------------
//
// Copyright (c) 2016 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ICARD_H__GLYMPSE__
#define ICARD_H__GLYMPSE__

namespace Glympse
{

/**
 * Exposes basic properties and a state of a card.
 *
 * Host application does not create or modify card objects directly. Instead it uses methods 
 * exposed by IGlympseCards.
 */
/*O*public**/ struct ICard : public IEventSink
{
    /**
     * Read only access functions.
     */

    /**
     * Get the unique card identifier.
     *
     * @return Unique card identifier.
     */
    public: virtual GString getId() = 0;

    /**
     * Get the type identifier.
     *
     * @return Card type identifier.
     */
    public: virtual GString getTypeId() = 0;

    /**
     * Gets the card name.
     *
     * @return Card Name
     */
    public: virtual GString getName() = 0;

    /**
     * Get the card state. See GC::CARD_STATE_* for valid states.
     *
     * @return The current card state.
     */
    public: virtual int32 getState() = 0;

    /**
     * Get the card member representing the self user.
     *
     * @return CardMember representing the self user.
     */
    public: virtual GCardMember getSelfMember() = 0;

    /**
     * Get the list of card members including the self user.
     *
     * @return CardMember list including the self user.
     */
    public: virtual GArray<GCardMember>::ptr getMembers() = 0;

    /**
     * Search the card member list for a member with the given id.
     * @param id The id of the card member to find.
     *
     * @return CardMember with the given id or null if none was found.
     */
    public: virtual GCardMember findMemberByMemberId(const GString& id) = 0;
    
    /**
     * Search the card member list for a member with the given user id.
     * @param id The id of the glympse user to find.
     *
     * @return CardMember with the given id or null if none was found.
     */
    public: virtual GCardMember findMemberByUserId(const GString& id) = 0;
    
    /**
     * Search the card member list for an invite with the given id.
     * @param id The id of the card invite to find.
     *
     * @return CardInvite with the given id or null if none was found.
     */
    public: virtual GCardInvite findInviteByInviteId(const GString& id) = 0;
    
    /**
     * Get the list of card invites.
     *
     * @return CardInvite list
     */
    public: virtual GArray<GCardInvite>::ptr getInvites() = 0;
    
    /**
     * Get the list of card objects.
     *
     * @return CardObject list
     */
    public: virtual GArray<GCardObject>::ptr getObjects() = 0;
    
    /**
     * Search the card object list for an object with the given id.
     * @param id The id of the card object to find.
     *
     * @return GCardObject with the given id or null if none was found.
     */
    public: virtual GCardObject findObjectByObjectId(const GString& objectId) = 0;

    /**
     * Get the card's activity object.
     *
     * @return CardActivity object for this card.
     */
    public: virtual GCardActivity getActivity() = 0;

    /**
     * Get the time the card was created.
     *
     * @return Card creation time in Epoch ms.
     */
    public: virtual int64 getCreatedTime() = 0;

    /**
     * Get the time the card was last modified.
     *
     * @return Card last modified time in Epoch ms.
     */
    public: virtual int64 getLastModifiedTime() = 0;
    
    /**
     * Card Membership Section
     */
    
    /**
     * Send an invite to the card.
     *
     * @param invite GCardInvite with fields set to indicate delivery.
     *
     * @return true if card was in a state that can send the invite or buffer it. false otherwise.
     */
    public: virtual bool sendCardInvite(const GCardInvite& invite) = 0;
    
    /**
     * Removes pending invite to join a card.
     *
     * @param invite Pending card invite to be removed.
     *
     * @return true if card invite removal was scheduled successfully.
     */
    public: virtual bool deleteCardInvite(const GCardInvite& invite) = 0;
    
    /**
     * Accepts request to join a card.
     *
     * @return true if card was in a state that can accept requests. false otherwise.
     */
    public: virtual bool acceptCardRequest(const GCardInvite& request) = 0;
    
    /**
     * Removes a member from the card. Can also be used to leave a card by passing the self member.
     *
     * @param Card Member to remove.
     *
     * @return true if the member can be removed. false otherwise.
     */
    public: virtual bool deleteMember(const GCardMember& member) = 0;

    /**
     * Card Modification functions.
     */

    /**
     * Update a cards name.
     *
     * @param name The name of the card to be set.
     *
     * @return true if the name of this card can be updated. false otherwise.
     */
    public: virtual bool updateName(const GString& name) = 0;

    /**
     * Starts location sharing with the given card ticket. Ticket should be created and passed in. This function
     * will handle creating an invite, activating the ticket and sharing it into the card.
     *
     * @param cardTicket Card Ticket to use for sharing. Must have GTicket filled in.
     * @param requestTicket Original Card Ticket being used to reply. Can be null.
     */
    public: virtual bool startSharing(const GCardTicket& cardTicket) = 0;

    /**
     * Stops location sharing in this card. If location sharing is not active or expired, this call does nothing.
     */
    public: virtual bool stopSharing() = 0;
    
    /**
     * Determines whether location request received within the card needs to be replied to.
     * The decision is made based on whether self member shared location to the card since
     * the moment when request had been generated.
     *
     * @param cardTicket Card location request received from another card member.
     * @return true if location request still needs to be addressed.
     */
    public: virtual bool shouldReply(const GCardTicket& cardTicket) = 0;

    /**
     * Starts a location request with the given ticket. 
     *
     * Ticket should describe the information that will be filled in on the receiver's side 
     * when creating a ticket. i.e. destination, duration.
     *
     * @param cardTicket Card Ticket to use for requesting. Must have GTicket filled in.
     */
    public: virtual bool startRequesting(const GCardTicket& cardTicket) = 0;

    /**
     * Stops the previous card location request.
     */
    public: virtual bool stopRequesting() = 0;

    /**
     * Declines a request to share location received from another card member.
     */
    public: virtual bool declineRequest(const GCardTicket& cardTicket) = 0;
    
    /**
     * Checks to see if the most recent event has been acknowledged.
     */
    public: virtual bool isAcknowledged() = 0;
    
    /**
     * Adds a GCardObject to this card's list of card objects.
     */
    public: virtual void addObject(const GCardObject& cardObject) = 0;
    
    /**
     * Removes a GCardObject from this card's list of card objects.
     */
    public: virtual void removeObject(const GCardObject& cardObject) = 0;
    
    /**
     * Creates and adds a custom event to this card's activity list
     */
    public: virtual void createEvent(const GString& eventType, const GPrimitive& data) = 0;
};
    
/*C*/typedef O< ICard > GCard;/**/
        
}

#endif // !ICARD_H__GLYMPSE__
