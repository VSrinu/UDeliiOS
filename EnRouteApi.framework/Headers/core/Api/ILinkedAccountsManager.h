//------------------------------------------------------------------------------
//
// Copyright (c) 2013 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ILINKEDACCOUNTSMANAGER_H__GLYMPSE__
#define ILINKEDACCOUNTSMANAGER_H__GLYMPSE__

namespace Glympse
{
    
/*O*public**/ struct ILinkedAccountsManager : public IEventSink
{
    /**
     * Determines whether or not the linked accounts manager has completed its initial
     * sync with the server.
     *
     * @returns true, if the initial sync is complete, false otherwise.
     */
    public: virtual bool isSynced() = 0;
    
    /**
     * Sends confirmation code required to link account of GC::LINKED_ACCOUNT_TYPE_PHONE of
     * GC::LINKED_ACCOUNT_TYPE_EMAIL type.
     *
     * Upon success, a GE::CONFIRMATION_CODE_SENT event is fired on LISTENER_CONFIRMATION_CODE.
     * Upon failure, a GE::CONFIRMATION_CODE_FAILED event is fired on LISTENER_CONFIRMATION_CODE.
     *
     * @param type The type of the account to be linked.
     * @param profile GPrimitive of CC#PRIMITIVE_TYPE_OBJECT type containing the profile
     * name and associated metadata. Use GlympseFactory static profile factory methods for
     * convenience.
     *
     * @return Event sink of GC::LISTENER_CONFIRMATION_CODE type.
     */
    public: virtual GEventSink confirm(const GString& type, const GPrimitive& profile) = 0;
    
    /**
     * Links an account of the specified type using the account profile information
     * provided.
     *
     * Upon success, a GE::ACCOUNT_LINK_SUCCEEDED event is fired on LISTENER_LINKED_ACCOUNTS.
     * Upon failure, a GE::ACCOUNT_LINK_FAILED event is fired on LISTENER_LINKED_ACCOUNTS.
     *
     * @param type The type of the account to be linked.
     * @param profile GPrimitive of CC#PRIMITIVE_TYPE_OBJECT type containing the profile 
     * name and associated metadata. Use GlympseFactory static profile factory methods for
     * convenience.
     *
     * @return A linked account object, or NULL if the request was invalid.
     */
    public: virtual GLinkedAccount link(const GString& type, const GPrimitive& profile) = 0;

    /**
     * Links an account of the specified type using the account profile information
     * provided, forcefully if necessary.
     *
     * Upon success, a GE::ACCOUNT_LINK_SUCCEEDED event is fired on LISTENER_LINKED_ACCOUNTS.
     * Upon failure, a GE::ACCOUNT_LINK_FAILED event is fired on LISTENER_LINKED_ACCOUNTS.
     *
     * @param type The type of the account to be linked.
     * @param profile GPrimitive of CC#PRIMITIVE_TYPE_OBJECT type containing the profile
     * name and associated metadata. Use GlympseFactory static profile factory methods for
     * convenience.
     * @param force If true, and the profile is valid, forces the link, transferring the 
     * account from another user account if necessary.
     *
     * @return A linked account object, or NULL if the request was invalid.
     */
    public: virtual GLinkedAccount link(const GString& type, const GPrimitive& profile, bool force) = 0;

    /**
     * Unlinks the account of the specified type.
     *
     * Upon success, a GE::ACCOUNT_UNLINK_SUCCEEDED event is fired on LISTENER_LINKED_ACCOUNTS.
     * Upon failure, a GE::ACCOUNT_UNLINK_FAILED event is fired on LISTENER_LINKED_ACCOUNTS.
     *
     * @param type The type of the account to be unlinked.
     *
     * @return A linked account object, or NULL if the request was invalid.
     */
    public: virtual GLinkedAccount unlink(const GString& type) = 0;
    
    /**
     * Refreshes an account of the specified type using the account profile information
     * provided.
     *
     * Upon success, a GE::ACCOUNT_REFRESH_SUCCEEDED event is fired on LISTENER_LINKED_ACCOUNTS.
     * Upon failure, a GE::ACCOUNT_REFRESH_FAILED event is fired on LISTENER_LINKED_ACCOUNTS.
     *
     * @param type The type of the account to be refreshed.
     * @param profile GPrimitive of CC#PRIMITIVE_TYPE_OBJECT type containing the profile
     * name and associated metadata. Use GlympseFactory static profile factory methods for
     * convenience.
     *
     * @return A linked account object, or NULL if the request was invalid.
     */
    public: virtual GLinkedAccount refresh(const GString& type, const GPrimitive& profile) = 0;

    /**
     * Retrieves a property previously set for the specified account type by name.
     *
     * @param type The type of the account to be interrogated.
     * @param name The name of the property to retrieve, qualified by the type.
     *
     * @return The value of the property requested in the form of a GPrimitive or NULL if the
     * type or property does not exist, or if an error occurred.
     */
    public: virtual GPrimitive getAccountProperty(const GString& type, const GString& name) = 0;

    /**
     * Sets a property for the specified account type by name.
     *
     * @param type The type of the account to be updated.
     * @param name The name of the property to update, qualified by the type.
     * @param value The value to set for the property.
     */
    public: virtual void setAccountProperty(const GString& type, const GString& name, const GPrimitive& value) = 0;

    /**
     * Retrieves the linked account for the specified type.
     *
     * @param type The type of the account to be retrieved.
     *
     * @return The linked account, or NULL if none exists.
     */
    public: virtual GLinkedAccount getAccount(const GString& type) = 0;

    /**
     * Retrieves the list of all linked accounts.
     *
     * @return The list of linked accounts.
     */
    public: virtual GArray<GLinkedAccount>::ptr getAccounts() = 0;
    
    /**
     * Retrieves the number of linked accounts satisfying the specified criteria.
     * 
     * @param loginEnabled Only consider accounts enabled for login.
     *
     * @return The number of linked accounts matching the specified criteria.
     */
    public: virtual int32 getCount(bool loginEnabled) = 0;

    /**
     * Refreshes the entire list of linked accounts and their status ("freshness").
     *
     * Upon success, a GE::ACCOUNT_LIST_REFRESH_SUCCEEDED event is fired on LISTENER_LINKED_ACCOUNTS.
     * Upon failure, a GE::ACCOUNT_LIST_REFRESH_FAILED event is fired on LISTENER_LINKED_ACCOUNTS.
     *
     * @return true, if the request to refresh the account list was initiated, false otherwise.
     */
    public: virtual bool refresh() = 0;
    
    /**
     * Determines if account required for sending the invite is linked to user's profile.
     *
     * @param invite Invite object to be analyzed.
     * @return true if platform is capable of sending the invite.
     */
    public: virtual bool canSend(const GInvite& invite) = 0;
};
    
/*C*/typedef O< ILinkedAccountsManager > GLinkedAccountsManager;/**/
    
}

#endif // !ILINKEDACCOUNTSMANAGER_H__GLYMPSE__
