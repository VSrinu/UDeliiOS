//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ITICKET_H__GLYMPSE__
#define ITICKET_H__GLYMPSE__

namespace Glympse 
{
     
/**
 * This class represents an actual received "Glympse" or sent "Glympse".
 * 
 * The term "Ticket" is synonymous with the term "Glympse" when referring to the object that is created and 
 * sent to recipients in order to share your location.
 * A ticket contains recipients, start and end times (and thus duration), a message, and a destination.
 * A ticket can be received from another Glympse user, allowing us to watch that user.
 * A ticket can also be sent to recipients, allowing them to watch the local user.
 * 
 * Tickets are created by Users. When you receive a ticket from another user,
 * that ticket grants you access to view that user for a specific amount of time.
 * Tickets that are received can be watched by calling the IGlympse#viewTicket method.
 * Once the ticket has been verified by the Glympse server, you will begin watching the user that sent the ticket. 
 * If you are not already watching this user from a previous ticket, the Glympse system will create a new
 * IUser object in your IUserManager collection. The IUser object contains 
 * a list of tickets you are watching for this user. The ticket you are watching will be added to this list.
 * You can call the IUser#getTickets method for a list of all tickets you have received from
 * a given user.
 *
 * When sending a ticket to another user, you will first create a new ITicket and then call
 * IGlympse#sendTicket to send the ticket to the recipients you have chosen.
 * The sent ticket will be transfered to your IHistoryManager collection.
 * You can monitor this ticket collection and the list of recipients within each ticket for viewer activity.
 */
/*O*public**/ struct ITicket : public IEventSink, public IComparable
{
    /**
     * Gets the internal ticket identifier of this ticket.
     *
     * @return The ticket identifier.
     */
    public: virtual GString getId() = 0;
    
    /**
     * Indicates whether the ticket object refers to incoming or outgoing ticket.
     *
     * @return true, for tickets API is watching. false for sent tickets.
     */ 
    public: virtual bool isWatching() = 0;
    
    /**
     * Indicates whether ticket is controlled by this device (application or process).
     * Ticket ownership only makes sense for outgoing tickets. 
     *
     * @return 'mine' property of a ticket.
     */
    public: virtual bool isMine() = 0;
    
    /**
     * The method returns opposite value to what isMine() returns.
     * This overridden method is provided for convenience.
     */
    public: virtual bool isSibling() = 0;
    
    /**
     * Returns the visibility of the ticket. Visibility is comprised of a location visibility 
     * value (GC::TICKET_VISIBILITY_KEY_LOCATION()) and an optional visibility context 
     * (GC::TICKET_VISIBILITY_KEY_CONTEXT()).
     *
     * @return a GPrimitive object representing the visibility of the ticket.
     */
    public: virtual GPrimitive getVisibility() = 0;
    
    /**
     * Determines the visibility of the ticket. This is a convenience method for quick visibility checking.
     * To retrieve the full visibility, use getVisibility().
     *
     * @return true, if the ticket is visible, false otherwise.
     */
    public: virtual bool isVisible() = 0;

    /**
     * Gets ticket code of the incoming Glympse. This method returns ticket invite code,
     * which was used to add this ticket for watching. The method always returns NULL for
     * outgoing tickets. 
     *
     * @return The ticket invite code for incoming tickets, NULL for outgoing tickets.
     */
    public: virtual GString getCode() = 0;

    /**
     * Gets the reference code of the ticket. Normally this would be the invite code of an invite request that
     * created the ticket or of a ticket invite with an attached reply request used to create this ticket.
     *
     * @return The ticket reference code.
     */
    public: virtual GString getReference() = 0;

    /**
     * Gets ticket state. See GlympseConstants for more details. 
     *
     * @return The ticket state. 
     */ 
    public: virtual int32 getState() = 0;
    
    /**
     * Gets the ticket owner. Changes to ownership are propagated using the GE::TICKET_TRANSFERRED event.
     *
     * @return The profile of the application that currently owns the ticket.
     */
    public: virtual GAppProfile getOwner() = 0;
    
    /**
     * Gets the user to whom this ticket belongs.
     *
     * @return The user object to whom the ticket belongs, or NULL if the ticket is as-yet unattached.
     */
    public: virtual GUser getUser() = 0;

    /**
     * This method takes into account ticket state (getState()) and ownership (isMine()).
     *
     * @return true is returned for self tickets in GC::TICKET_STATE_ACTIVE state.
     */
    public: virtual bool isActive() = 0;
    
    /**
     * Checks whether ticket is marked as completed. Completed tickets (both incoming and outgoing)
     * are immutable from the perspective of host application. They cannot change their state on their own
     * and cannot be changed from outside.
     *
     * Platform broadcasts GE::TICKET_COMPLETED event to ticket subscribers, when transition happens.
     *
     * Host application should not expect any events from incoming ticket since it turns into completed state.
     * It is still allowed to delete outgoing ticket (using ITicket::deleteTicket()) from the history even
     * after its completion.
     *
     * @return The value of true means that ticket is completed and can no longer be modified.
     */
    public: virtual bool isCompleted() = 0;
    
    /**
     * Returns the recipient list collection for this ticket as an array of </code>IInvite</code> objects.
     * You can only query the recipients for tickets you created (tickets you retrieve from the 
     * IHistoryManager#getTickets method).
     * If you call this on a ticket you are watching (tickets you retrieve from the IUser#getTickets method),
     * this method will simply return an empty list. 
     * Recipient information is private to the user that created the ticket they belong to.
     *
     * @return An array of IInvite objects for this ticket.
     */
    public: virtual GArray<GInvite>::ptr getInvites() = 0;
        
    /**
     * Gets the duration of the ticket.
     * This is essentially the difference between the start time and the expire time of the ticket.
     * 
     * For outgoing tickets, which are not yet sent, it returns current ticket duration for the ticket.
     *
     * @return The duration in milliseconds.
     */
    public: virtual int32 getDuration() = 0;
    
    /**
     * Gets the epoch time (milliseconds since 1/1/1970) that the ticket was created.
     * This is a Glympse server time. If you need to compare it to the current system time, 
     * you should use the IGlympse#getTime method to obtain an accurate system time.
     *
     * @return The epoch time (milliseconds since 1/1/1970) that the ticket was created.
     */
    public: virtual int64 getStartTime() = 0;
    
    /**
     * Gets the epoch time (milliseconds since 1/1/1970) that the ticket will expire.
     * This is a Glympse server time. If you need to compare it to the current system time, 
     * you should use the IGlympse#getTime method to obtain an accurate system time.
     *
     * @return The epoch time (milliseconds since 1/1/1970) that the ticket was created.
     */
    public: virtual int64 getExpireTime() = 0;
    
    /**
     * Gets the optional message text associated with this ticket.
     *
     * @return The optional message text associated with this ticket.
     * Will be NULL for no message.
     */
    public: virtual GString getMessage() = 0;
    
    /**
     * Gets the optional destination that is associated with this ticket.
     *
     * @return The optional destination that is associated with this ticket. 
     * Will be NULL for no destination.
     */
    public: virtual GPlace getDestination() = 0;
    
    /**
     * Returns the historical track points for this ticket. These locations are locations
     * that have been successfully transmitted to the Glympse server for this user.
     * 
     * The Glympse server and Glympse API will trim this list of points to a
     * manageable duration. Currently, the list will contain a max of 10 minutes
     * worth of data.
     *
     * @return The list of track points for this user that have successfully been transmitted to the Glympse server.
     */     
    public: virtual GTrack getTrack() = 0;
    
    /**
     * This method remembers ETA value and transmits it to all viewers.
     *
     * Make sure that platform operates in GC::ETA_MODE_EXTERNAL mode.
     * Otherwise external updates will interfere with the values calculated internally.
     *
     * @param eta New ETA value in milliseconds. Pass 0 to clear ETA. 
     */ 
    public: virtual void updateEta(int64 eta) = 0;
    
    /**
     * Gets ETA (Estimated Time of Arrival) for the user API is watching. 
     * The method performs required calculations to provide caller with correct value.
     *
     * The following approach is used to determine returned value:
     * - ETA = ETA_RAW - ( NOW - ETA_TS )
     * where
     * - ETA is the value returned by this method;
     * - ETA_RAW is originally determined ETA value;
     * - ETA_TS is timestamp in the past, when ETA_RAW was determined.
     *
     * As it is seen from the explanation above, the value returned by this 
     * method changes over time, even if no updates are coming from sender. 
     *
     * Note that GE::TICKET_ETA_CHANGED is sent only, when ETA changes significantly
     * (new value is received from sender). 
     *
     * @return ETA in milliseconds. O, if ETA is not available. 
     */ 
    public: virtual int64 getEta() = 0;
    
    /**
     * This method remembers new predicted route and transmits it to all viewers.
     *
     * Make sure that platform operates in GC::ETA_MODE_EXTERNAL mode.
     * Otherwise external updates will interfere with the values calculated internally.
     *
     * @param route New route to be applied. Pass NULL to clear currently applied route.
     */
    public: virtual void updateRoute(const GTrack& route) = 0;
    
    /**
     * Gets predicted route for the user API is watching. 
     * 
     * @return Predicted route. NULL, if route is not available. 
     */
    public: virtual GTrack getRoute() = 0;
    
    /**
     * Gets travel mode. 
     *
     * Ticket listeners are notified on changes in this property using GE::TICKET_TRAVEL_MODE_CHANGED event.
     *
     * @return Travel mode descriptor or NULL.
     */
    public: virtual GTravelMode getTravelMode() = 0;
    
    /**
     * Gets the IInvite object that matches the given invite code.
     */
    public: virtual GInvite findInviteByCode(const GString& code) = 0;

    /**
     * Gets the IInvite object that matches the given address.
     */
    public: virtual GInvite findInviteByAddress(const GString& address) = 0;

    /**
     * Gets the IInvite object that matches the given type.
     */
    public: virtual GInvite findInviteByType(int32 type) = 0;
    
    /**
     * Runs a check to determine whether invite like that can be added to the ticket.
     * The method validates invite consistency and looks for identical invites that are already registered.
     *
     * Invite type and other properties are taken into account during comparison. 
     * The following rules are applied:
     * - Only single invite of GC::INVITE_TYPE_TWITTER, GC::INVITE_TYPE_FACEBOOK, 
     *   GC::INVITE_TYPE_EVERNOTE, GC::INVITE_TYPE_CLIPBOARD can be added to the ticket.
     * - Numerous invites of GC::INVITE_TYPE_LINK type can be registered.
     * - Invites of all other types come with required address field. Addresses are
     *   compared to determine whether invite already presents on the list.
     *
     * @param invite Invite object to be tested.
     * @return true if invite can still be added to the ticket.
     */
    public: virtual bool canAddInvite(const GInvite& invite) = 0;

    /**
     * Adds invite to the ticket. This leads to creating invite code (on server side) and
     * delivering it to the recipient using mechanism conditioned by invite type.
     *
     * The method can be called both before and after ticket is sent. 
     * It is only possible to add invites to active self outgoing tickets.
     *
     * @return true on success. false is returned if any of the following happens:
     * - invite is configured improperly;
     * - invite is a duplicate of another invite already added to the ticket.
     * - ticket does not support adding invites (incoming ticket).
     */
    public: virtual bool addInvite(const GInvite& invite) = 0;
    
    /**
     * Removes invite from the ticket and invalidates associated invite code.
     * Ticket information will no longer be accessible through this invite.
     *
     * @return true on success.
     */
    public: virtual bool deleteInvite(const GInvite& invite) = 0;
    
    /**
     * Determines whether ticket is currently being watched. 
     * The method only makes sense for outgoing tickets. 
     *
     * @return Returns true, if ticket is currently being watched.
     */
    public: virtual bool isSomeoneWatching() = 0;
    
    /**
     * Specifies end time for Glympse request. End time means that
     * requester expects for requestee to share his/her location till this 
     * point in the future. This property is optional and is only used as a 
     * recommendation (or even ignored) at the receiving end.
     *
     * The method does not make any affect, if called against incoming or outgoing ticket.
     *
     * @param endTime UTC time in milliseconds.
     */
    public: virtual void setRequestEndTime(int64 endTime) = 0;

    /**
     * Gets the request ticket if there is one.
     *
     * @return Request Ticket. NULL if there is not one set.
     */
    public: virtual GTicket getRequestTicket() = 0;

    /**
     * For request tickets sets the no reply flag.
     *
     * @param requestNoReply true if requests should be ignored.
     */
    public: virtual void setRequestNoReply(bool requestNoReply) = 0;

    /**
     * For request tickets, gets the no reply flag.
     *
     * @return true if the request should be ignored.
     */
    public: virtual bool getRequestNoReply() = 0;

    /**
     * For request tickets, sets the request scenario.
     *
     * @param requestScenario Description of request scenario.
     */
    public: virtual void setRequestScenario(const GString& requestScenario) = 0;

    /**
     * For request tickets, gets the request scenario if there is one.
     *
     * @return Description of request scenario.
     */
    public: virtual GString getRequestScenario() = 0;

    /**
     * Sets the visibility of the ticket. Visibility is comprised of a location visibility specification
     * (either GC::TICKET_VISIBILITY_LOCATION_HIDDEN() or GC::TICKET_VISIBILITY_LOCATION_VISIBLE()) and
     * and optional context.
     *
     * @param visibility The location visibility (visible or hidden).
     * @param context An optional context string.
     *
     * @return true, if the visibility was changed, false if an error occurred.
     */
    public: virtual bool setVisibility(const GString& visibility, const GString& context) = 0;

    /**
     * Modifies an active sent Glympse, allowing you to add recipients, change the duration, expire the ticket, 
     * change the message, and/or change the destination.
     * 
     * The modify method allows you to change the duration of the ticket.
     * The duration parameter specifies how much time from 'now' you want the ticket to last.
     * Therefore, passing a value of 0 will instantly expire the ticket. 
     * If you do not wish to change the ticket duration, you can pass the constant GC::DURATION_NO_CHANGE
     * to the modify() method.
     * 
     * To modify the message, simply pass in a new message string. 
     * To not modify the message, you should pass in NULL.
     * 
     * To modify the destination, simply pass in a new IPlace object for the destination.
     * To not modify the destination, you should pass in NULL.
     *
     * @param remaining The duration in milliseconds from 'now' until the time when the ticket should expire.
     * Pass 0 to expire now. Pass DURATION_NO_CHANGE to not modify.
     * @param message The new message text. Pass NULL to not modify.
     * @param destination The new destination. Pass NULL to not modify.
     * @return true, if successful. false, if this ticket is not found in your sent ticket list.
     */
    public: virtual bool modify(int32 remaining, const GString& message, const GPlace& destination) = 0;
    
    /**
     * Extends ticket for the amount of time specified by the argument.
     *
     * @param interval Amount of time in milliseconds to extend the ticket for.
     */
    public: virtual bool extend(int32 interval) = 0;

    /**
     * Sets the name of the ticket as specified. Used mainly for describing a favorite.
     *
     * @param name Name of the ticket.
     */
    public: virtual void setName(const GString& name) = 0;

    /**
     * Gets the name of the ticket. Used mainly for favorites to describe them.
     *
     * @return The name of the ticket. Usually null except for favorites.
     */
    public: virtual GString getName() = 0;

    /**
     * Clears message or destination property of the ticket. 
     *
     * @param message Specify true, if you want to clear the message.
     * @param destination Specify true, if you want to clear the destination.
     * @return true, if successful. false, if this ticket is not found in your sent ticket list.     
     */
    public: virtual bool clear(bool message, bool destination) = 0;
    
    /**
     * Expires currently active ticket. Once expiration is scheduled 
     * ticket remains in GC::TICKET_STATE_EXPIRING until response is received from the server.
     *
     * Both self and sibling tickets can be expired.
     * The method takes affect only if ticket is fully constructed and initialized.
     *
     * @return true, if ticket expiration is scheduled.
     */
    public: virtual bool expire() = 0;

    /**
     * Provides a chance to append custom property to the ticket.
     *
     * @param partnerId Partner specific identifier. This value defines namespace for all partner properties. 
     * Value of 0 belongs to standard Glympse properties (like nickname, message, etc.). So partner id of 0
     * (as well as negative values) are considered to be incorrect. You should use other tools from
     * Client API to modify standard properties. 
     * @param name Custom property name.
     * @param value Object that represents property value. 
     * 
     * @return Returns true, if operation was scheduled correctly. Property is appended to data stream
     * asynchronously. Returns false, if one of arguments was considered to be incorrect, and 
     */     
    public: virtual bool appendData(int64 partnerId, const GString& name, const GPrimitive& value) = 0;
    
    /**
     * Gets property associated with the ticket object. 
     *
     * @param partnerId Partner identifier.
     * @param name Property name.
     * @return Property value or NULL, if property with such name is not set by the partner.
     */
    public: virtual GPrimitive getProperty(int64 partnerId, const GString& name) = 0;
    
    /**
     * Gets property GDataRow associated with the ticket object.
     *
     * @param partnerId Partner identifier.
     * @param name Property name.
     * @return Property data value or NULL, if property with such name is not set by the partner.
     */
    public: virtual GDataRow getPropertyData(int64 partnerId, const GString& name) = 0;
    
    /**
     * Returns a enumeration of all partner ids that have appened properties to this ticket.
     *
     * @return GEnumeration of partnerIds as GLong values. GLong::longValue() may be used to retrieve the int64 representation of the partner id.
     */
    public: virtual GEnumeration<GLong>::ptr getPartnerIds() = 0;
    
    /**
     * Returns a readonly GMap of all properties associated with this partner id.
     *
     * @param partnerId Partner identifier.
     * @return Property data values or NULL, if no properties exist for that partner id.
     */
    public: virtual GMap<GString, GDataRow>::ptr getPartnerData(int64 partnerId) = 0;
    
    /**
     * Requests for ownership over this ticket to be passed to this device.
     * Ticket ownership is not passed instantly. Round trip to the server is required for this purpose.
     * See GE::TICKET_TRANSFERRED for more details.
     *
     * The operation only makes sense for active (!) outgoing (!) sibling (!) tickets.
     *
     * @return true if ownership passing was initiated successfully.
     */
    public: virtual bool own() = 0;
    
    /**
     * Begins the process of handing off this single ticket to new owner service (Mojio, another invite code, etc.). If this ticket has already been created on the server, it will be
     * handed off right away. If not, it will be handed off after it has been created on the server.
     *
     * @param providerId The ID string that identifies the desired new owner to the server.
     * @param providerData The GPrimitive of OBJECT type that provides the data required for handoff to the server.
     */
    public: virtual void setOwnership(const GString& providerId, const GPrimitive& providerData) = 0;
    
    /**
     * Delete this sent ticket.
     * 
     * Once a ticket is successfully deleted from the Glympse server, it will be removed from your sent ticket list 
     * ("Glympse history") and will not be viewable by any recipients of that ticket.
     *
     * @return true, if successful. false, if this ticket is not found in your sent ticket list.
     */    
    public: virtual bool deleteTicket() = 0;
    
    /**
     * Clones ticket object including the following properties:
     * - invites;
     * - duration; 
     * - message;
     * - destination
     * (basically all configurable properties of outgoing tickets).
     *
     * This method should be used to produce copy of any of existing tickets and
     * store it for later use (save as a favorite or send). 
     *
     * It is not possible to reuse ticket objects. It is required to create a copy
     * of ticket object to be able to resent outgoing ticket or reply to incoming ticket. 
     *
     * Once ticket object is cloned it is out of sync with its clone. None of the 
     * changes made to any of those objects are reflected into another. 
     *
     * @return Deep copy of the current ticket object is returned. 
     */
    public: virtual GTicket clone() = 0;            
};
    
}

#endif // !ITICKET_H__GLYMPSE__
