//------------------------------------------------------------------------------
//
// Copyright (c) 2013 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ILINKEDACCOUNT_H__GLYMPSE__
#define ILINKEDACCOUNT_H__GLYMPSE__

namespace Glympse
{
    
/*O*public**/ struct ILinkedAccount : public ICommon
{
    /**
     * Gets the type of the linked account.
     *
     * @return The account type, which will be one of the GC#LINKED_ACCOUNT_TYPE constants.
     */
    public: virtual GString getType() = 0;

    /**
     * Gets the state of the linked account which is an indication of the current state of 
     * the account in relation to the server, including transient states such as "linking",
     * "unlinking" and "refreshing".
     *
     * @return The linking state, which will be one of the GC#LINKED_ACCOUNT_STATE constants.
     */
    public: virtual int32 getState() = 0;

    /**
     * Gets the status of the linked account which is an indication of the last known state
     * of the account metadata (i.e., tokens, secrets, etc.). Accounts that are in the "linked"
     * state may have a status of "refresh needed", for example, or "ok".
     *
     * @return The account status, which will be one of the GC#LINKED_ACCOUNT_STATUS constants.
     */
    public: virtual int32 getStatus() = 0;

    /**
     * Gets the ID of the linked account. This is account-specific, but is typically an opaque, 
     * unique identifier in the third-party service.
     *
     * @return The acccount identifier.
     */
    public: virtual GString getId() = 0;
    
    /**
     * Gets the username associated with the linked account. This is account-specific, but is
     * typically a unique identifier used for login, such as a login name or an email address.
     *
     * @return The username.
     */
    public: virtual GString getUserName() = 0;

    /**
     * Gets the display name associated with the linked account. This is account-specific, but
     * is typically either the name of the user, a login name or screen name.
     *
     * @return The display name, or NULL if none exists.
     */
    public: virtual GString getDisplayName() = 0;

    /**
     * Determines whether or not the type of the linked account is enabled for federated login.
     *
     * @return The login state, which will be one of the GC#LINKED_ACCOUNT_LOGIN constants.
     */
    public: virtual int32 getLogin() = 0;
    
    /**
     * Gets detailed server error information. This method returns NULL except in the context
     * of LISTENER_LINKED_ACCOUNTS event propagation.
     *
     * @return Error details, or NULL if no details are available or no error occurred.
     */
    public: virtual GServerError getError() = 0;
};
    
/*C*/typedef O< ILinkedAccount > GLinkedAccount;/**/
    
}

#endif // !ILINKEDACCOUNT_H__GLYMPSE__
