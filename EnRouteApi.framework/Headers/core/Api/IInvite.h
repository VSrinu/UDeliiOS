//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IINVITE_H__GLYMPSE__
#define IINVITE_H__GLYMPSE__

namespace Glympse 
{

/**
 * IInite does not actually refer any of these interfaces.
 */
/*C*/
struct IUser;
typedef O< IUser > GUser;
struct ITicket;    
typedef O< ITicket > GTicket;
struct IInvite;
typedef O< IInvite > GInvite;
/**/
    
/*C*/
struct IInviteViewers;
typedef O< IInviteViewers > GInviteViewers;
/**/

/**
 * Defines a single recipient of a Glympse. A recipient consists of a recipient type (email, SMS, etc.), 
 * an address string, a friendly name, the status of the invitation, and recipient viewing information.
 */
/*O*public**/ struct IInvite : public IComparable
{
    /**
     * Gets the type of this recipient. 
     * See GlympseConstants for complete list of all valid recipient types. 
     */
    public: virtual int32 getType() = 0;    

    /**
     * Gets the subtype of this recipient.
     */
    public: virtual GString getSubtype() = 0;
    
    /**
     * Gets the display name of this recipient.
     */
    public: virtual GString getName() = 0;    
    
    /**
     * Gets the email address or phone number of this recipient.
     */
    public: virtual GString getAddress() = 0;

    /**
     * Sets brand parameter of the invite. Brand belongs to API key and is used to
     * customize invite appearance and viewing experience.
     *
     * The method is optional. By default invite derives all its properties from API key.
     *
     * This method makes effect only if invoked before invite is actually created.
     */
    public: virtual void setBrand(const GString& brand) = 0;
    
    /**
     * This method is provided for convenience. It applies brand,
     * only if it is not applied yet (getBrand() returns NULL).
     */
    public: virtual void applyBrand(const GString& brand) = 0;
    
    /**
     * Gets currently set brand for the invite or NULL, if brand is not set.
     */
    public: virtual GString getBrand() = 0;
    
    /**
     * Overrides default invite visibility. Invite visibility flag indicates
     * whether recipient information associated with this invite (invite type, name and address)
     * is exposed through other invites belonging to the same outgoing ticket.
     *
     * Most of these invites are sent to named groups ('!'-groups).
     * In which case all other invitees see the list of groups mentioned on the same ticket.
     * The idea behind public invites sent to named groups is similar to the concept of hashtags
     * actively adopted in microblogging.
     *
     * All invites are invisible by default.
     */
    public: virtual void setVisible(bool visible) = 0;
    
    /**
     * Checks whether invite is visible. See setVisible() for more details. 
     */
    public: virtual bool isVisible() = 0;
    
    /**
     * Returns true it invite is supposed to be created by the platform but not delivered.
     */
    public: virtual bool isCreateOnly() = 0;

    /**
     * Sets if the invite is supposed to be created by the platform but not delivered.
     */
    public: virtual void setCreateOnly(bool createOnly) = 0;

    /**
     * Gets the Glympse code that was sent to this recipient.
     */
    public: virtual GString getCode() = 0;
    
    /**
     * Gets the Glympse reference that should be used when accessing tickets through this invite.
     */
    public: virtual GString getReference() = 0;

    /**
     * Sets the Glympse reference that should be used when accessing tickets through this invite.
     */
    public: virtual void setReference(const GString& reference) = 0;

    /**
     * Gets the URL that was sent to this recipient.
     */
    public: virtual GString getUrl() = 0;    
    
    /**
     * Gets invite delivery state. 
     */ 
    public: virtual int32 getState() = 0;
    
    /**
     * Gets the epoch time (milliseconds since 1/1/1970) of when this invite was created.
     */    
    public: virtual int64 getCreatedTime() = 0;
    
    /**
     * Gets the epoch time (milliseconds since 1/1/1970) of when this invite was last viewed.
     */
    public: virtual int64 getLastViewTime() = 0;    
    
    /**
     * Gets total amount of unique Glympse viewers. 
     *
     * The following objects could act as unique Glympse viewers:
     * - Browser instance (or set of browsers sharing the same cookies space);
     * - Glympse application (or any other application build on top of Glympse Client API). 
     * This means that page refresh or even browser restart does not lead to increasing views count. 
     *
     * This count is forever increasing. It does not represent current amount of viewers. 
     * It is possible that nobody views Glympse at the moment, but the value returned by this method
     * remains high. getLastViewTime() should be used to get adequate information on how long ago     
     * the invite was viewed last time. 
     */
    public: virtual int32 getViewers() = 0;
    
    /**
     * Gets total amount of Glympse users currently viewing the Glympse through this invite code.
     * Returned valur goes up and down over time.
     */
    public: virtual int32 getViewing() = 0;
    
    /**
     * Gets access to the collection of all distinct viewers of this invite.
     *
     * @return An object of GInviteViewers type or NULL if viewer tracking is not enabled.
     */
    public: virtual GInviteViewers getViewerUsers() = 0;
    
    /**
     * Gets access to the collection of currently active invite viewers.
     * 
     * @return An object of GInviteViewers type or NULL if viewer tracking is not enabled.
     */
    public: virtual GInviteViewers getViewingUsers() = 0;
    
    /**
     * The method should be invoked by client code, when the recipient state becomes GC::RECIPIENT_STATE_NEEDTOSEND.
     * Recipient state is changed to GC::RECIPIENT_STATE_CLIENTSENDING.
     * 
     * This method does not send any events to ticket subscribers, as the action is initiated by client. 
     *
     * @return true on success. The method returnes false, when it has no effect due to being called on 
     * inappropriate recipient. 
     */ 
    public: virtual bool initiateClientSideSend() = 0;    
    
    /**
     * This method should be invoked, when invite delivery is complete, cancelled or failed. 
     * Recipient state is changed to either GC::RECIPIENT_STATE_SUCCEEDED or GC::RECIPIENT_STATE_FAILED_TO_SEND
     * depending on the value of succeeded argument.
     * 
     * This method does not send any events to ticket subscribers, as the action is initiated by client. 
     *
     * @param succeeded Indicates invite delivery success. 
     * @return true on success. The method returnes false, when it has no effect due to being called on 
     * inappropriate recipient. 
     */ 
    public: virtual bool completeClientSideSend(bool succeeded) = 0;
    
    /**
     * This method provides client with a message text to be sent to invite recipient. 
     *
     * The use of this function is optional, but it is highly recommended.
     * However, when formating the message you must include invite URL (returned by getUrl method).
     * It is not required to do, when using this method (formatForSMS).
     *
     * @return Invite text including URL for viewing, user display name (optional) and message (optional).
     * NULL is returned, if invite should not be delivered by client.
     */    
    public: virtual GString getText() = 0;        
    
    /**
     * This method attaches a request ticket to this ticket.
     *
     * This function should be used to attach a ticket representing the ticket which should be sent
     * as a response to the ticket being attached to.
     *
     * @param requestTicket The request ticket to be attached.
     */
    public: virtual void setRequestTicket(const GTicket& requestTicket) = 0;

    /**
     * This method retrieves the request ticket attached to this ticket.
     *
     * When generating a reply to a ticket use this function to see if the originator of the ticket
     * has populated it with a preferred method of reply.
     *
     * @return A ticket prepopulated with the preferred data to respond to this ticket.
     */
    public: virtual GTicket getRequestTicket() = 0;

    /**
     * This method returns error information received from the server in cases where the invite state is
     * GC#INVITE_STATE_FAILED_TO_CREATE.
     * 
     * @return Error details, or NULL if no details are available or no error occurred.
     */
    public: virtual GServerError getError() = 0;
    
    /**
     * Clones invite object including the following properties:
     * - type;
     * - name; 
     * - address;
     * (basically all properties required to deliver the invite).
     *
     * @return Deep copy of the current invite object is returned. 
     */
    public: virtual GInvite clone() = 0;  
};
    
}

#endif // !IINVITE_H__GLYMPSE__
