//------------------------------------------------------------------------------
//
// Copyright (c) 2013 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef CONVERSATIONHELPER_H__TOOLBOX__GLYMPSE__
#define CONVERSATIONHELPER_H__TOOLBOX__GLYMPSE__

namespace Glympse
{
namespace Toolbox
{

/**
 * The class implements a persisted mapping between a user-defined identifier
 * and a set of related Glympse tickets. In order for it to be able to lookup
 * tickets, an instance of the Glympse Client API must be specified using the
 * attach(...) method. If no instance is attached, or if the attached instance
 * has not been started or has not sync'd with the Glymspe server, it will not
 * be possible to perform Glympse ticket lookups (though the basic mapping
 * functionality for invite codes will still be available).
 */
/*O*public**/ class ConversationHelper : public Common< ICommon >
{
    /**
     * Public section
     */

    /**
     * Constructs a conversation mapping helper for incoming and outgoing tickets.
     *
     * @param name The name of the persisted file on disk.
     */
    public: ConversationHelper(const GCommonObj& context, const GString& name)
    {
        _glympse = NULL;
        _storage = CoreFactory::createStorage(context, name);

        // Load the persisted ticket mapping; if nothing has been persisted, then create
        // an empty storage container for new mappings.
        _cache = _storage->load();
        if ( _cache == NULL )
        {
            _cache = CoreFactory::createPrimitive(CC::PRIMITIVE_TYPE_OBJECT);
        }
    }

    /**
     * Initializes the helper.
     *
     * @param glympse An instance of the Glympse Client API platform.
     */
    public: void attach(const GGlympse& glympse)
    {
        // If a Glympse Client API instance has already been attached, or the specified
        // instance is invalid, exit now.
        if (( NULL != _glympse ) || ( NULL == glympse ))
        {
            return;
        }

        _glympse = glympse;
    }

    /**
     * Tears down the helper.
     */
    public: void detach()
    {
        // If the Glympse Client API instance was never initialized, exit now.
        if ( NULL == _glympse )
        {
            return;
        }

        _glympse = NULL;
    }

    /**
     * Adds a ticket to the conversation with the specified ID. This handles both
     * incoming and outgoing tickets.
     *
     * NOTE: Assumes that there is only ever one outgoing ticket associated with a
     * given conversation, while any number of incoming tickets are supported.
     *
     * @param conversationId The conversation ID to which this ticket is associated.
     * @param ticket The ticket to associate with this conversation.
     * @returns true if the ticket was successfully added, false otherwise.
     */
    public: bool addTicket(const GString& conversationId, const GTicket& ticket)
    {
        // If the specified ticket is NULL, exit now.
        if ( NULL == ticket )
        {
            return false;
        }

        // If this ticket is an incoming ticket (i.e., it's being viewed), then add
        // it to the array of incoming tickets.
        if ( ticket->isWatching() )
        {
            return addIncomingInviteCode(conversationId, ticket->getCode());
        }
        // Otherwise, set it as the outgoing ticket. This will overwrite any outgoing
        // ticket previously set for this conversation.
        else if ( ticket->getInvites()->length() > 0 )
        {
            return addOutgoingInviteCode(conversationId, ticket->getInvites()->at(0)->getCode());
        }

        return false;
    }

    /**
     * Removes a ticket from the conversation with the specified ID. This handles both
     * incoming and outgoing tickets.
     *
     * NOTE: Assumes that there is only ever one outgoing ticket associated with a
     * given conversation, while any number of incoming tickets are supported.
     *
     * NOTE: This method does not return a bool "success" indication because there are
     * cases where GPrimitive does not provide us sufficient information to determine
     * whether or not the operation was successful...
     *
     * @param conversationId The conversation ID to which this ticket is associated.
     * @param ticket The ticket to remove from this conversation.
     */
    public: void removeTicket(const GString& conversationId, const GTicket& ticket)
    {
        // If the specified ticket is NULL, exit now.
        if ( NULL == ticket )
        {
            return;
        }

        // If this ticket is an incoming ticket (i.e., it's being viewed) then remove,
        // it from the array of incoming tickets.
        if ( ticket->isWatching() )
        {
            removeIncomingInviteCode(conversationId, ticket->getCode());
        }
        // Otherwise, remove it as the outgoing ticket.
        else if ( ticket->getInvites()->length() > 0 )
        {
            removeOutgoingInviteCode(conversationId, ticket->getInvites()->at(0)->getCode());
        }
    }

    /**
     * Adds an outgoing invite code to the conversation with the specified ID.
     *
     * NOTE: Assumes that there is only ever one outgoing ticket associated with a
     * given conversation, while any number of incoming tickets are supported.
     *
     * @param conversationId The conversation ID to which this ticket is associated.
     * @param code The outgoing invite code to associate with this conversation.
     * @returns true if the ticket was successfully added, false otherwise.
     */
    public: bool addOutgoingInviteCode(const GString& conversationId, const GString& code)
    {
        // If either the conversation ID or the specified invite code is NULL, exit now.
        if (( NULL == conversationId ) || ( NULL == code ))
        {
            return false;
        }

        // Get the cached data for this conversation. If the cache contains no data
        // associated with this conversation, initialize storage and an empty array
        // for incoming invite codes.
        GPrimitive conversation = _cache->get(conversationId);
        if ( NULL == conversation )
        {
            conversation = CoreFactory::createPrimitive(CC::PRIMITIVE_TYPE_OBJECT);
            conversation->put(CoreFactory::createString("incoming"), CoreFactory::createPrimitive(CC::PRIMITIVE_TYPE_ARRAY));

            _cache->put(conversationId, conversation);
        }

        // Set the outgoing invite code. This will overwrite any outgoing invite code
        // previously set for this conversation.
        conversation->put(CoreFactory::createString("outgoing"), code);

        // Save the cache to persisted storage.
        _storage->save(_cache);

        return true;
    }

    /**
     * Adds an incoming invite code to the conversation with the specified ID.
     *
     * NOTE: Assumes that there is only ever one outgoing ticket associated with a
     * given conversation, while any number of incoming tickets are supported.
     *
     * @param conversationId The conversation ID to which this ticket is associated.
     * @param code The incoming invite code to associate with this conversation.
     * @returns true if the ticket was successfully added, false otherwise.
     */
    public: bool addIncomingInviteCode(const GString& conversationId, const GString& code)
    {
        // If either the conversation ID or the specified invite code is NULL, exit now.
        if (( NULL == conversationId ) || ( NULL == code ))
        {
            return false;
        }

        // Get the cached data for this conversation. If the cache contains no data
        // associated with this conversation, initialize storage and an empty array
        // for incoming invite codes.
        GPrimitive conversation = _cache->get(conversationId);
        if ( NULL == conversation )
        {
            conversation = CoreFactory::createPrimitive(CC::PRIMITIVE_TYPE_OBJECT);
            conversation->put(CoreFactory::createString("incoming"), CoreFactory::createPrimitive(CC::PRIMITIVE_TYPE_ARRAY));

            _cache->put(conversationId, conversation);
        }

        // Add this invite code to the array of incoming invite codes. To protect
        // against the same invite code from being added twice, we first attempt to
        // remove the specified code from the array before adding it back.
        GPrimitive incoming = conversation->get(CoreFactory::createString("incoming"));
        remove(incoming, code);
        incoming->put(CoreFactory::createPrimitive(code));

        // Save the cache to persisted storage.
        _storage->save(_cache);

        return true;
    }

    /**
     * Removes an outgoing invite code from the conversation with the specified ID.
     *
     * NOTE: Assumes that there is only ever one outgoing ticket associated with a
     * given conversation, while any number of incoming tickets are supported.
     *
     * NOTE: This method does not return a bool "success" indication because there are
     * cases where GPrimitive does not provide us sufficient information to determine
     * whether or not the operation was successful...
     *
     * @param conversationId The conversation ID to which this ticket is associated.
     * @param code The outgoing invite code to remove from this conversation.
     */
    public: void removeOutgoingInviteCode(const GString& conversationId, const GString& code)
    {
        // If either the conversation ID or the specified invite code is NULL, exit now.
        if (( NULL == conversationId ) || ( NULL == code ))
        {
            return;
        }

        // Get the cached data for this conversation. If the cache contains no data
        // associated with this conversation, exit now.
        GPrimitive conversation = _cache->get(conversationId);
        if ( NULL == conversation )
        {
            return;
        }

        // If the cache contains no outgoing invite code, exit now.
        GPrimitive outgoing = conversation->get(CoreFactory::createString("outgoing"));
        if ( NULL == outgoing )
        {
            return;
        }

        // If the outgoing invite code in the cache is the same as the specified
        // code, remove it.
        if ( outgoing->getString()->equals(code) )
        {
            conversation->remove(CoreFactory::createString("outgoing"));

            // Now that we've removed the outgoing invite code, if the size of the incoming
            // invite code array is empty, we can delete the entire entry for this conversation.
            if ( conversation->get(CoreFactory::createString("incoming"))->size() == 0 )
            {
                _cache->remove(conversationId);
            }
        }

        // Save the cache to persisted storage.
        _storage->save(_cache);
    }

    /**
     * Removes an incoming invite code from the conversation with the specified ID.
     *
     * NOTE: Assumes that there is only ever one outgoing ticket associated with a
     * given conversation, while any number of incoming tickets are supported.
     *
     * NOTE: This method does not return a bool "success" indication because there are
     * cases where GPrimitive does not provide us sufficient information to determine
     * whether or not the operation was successful...
     *
     * @param conversationId The conversation ID to which this ticket is associated.
     * @param code The incoming invite code to remove from this conversation.
     */
    public: void removeIncomingInviteCode(const GString& conversationId, const GString& code)
    {
        // If either the conversation ID or the specified invite code is NULL, exit now.
        if (( NULL == conversationId ) || ( NULL == code ))
        {
            return;
        }

        // Get the cached data for this conversation. If the cache contains no data
        // associated with this conversation, exit now.
        GPrimitive conversation = _cache->get(conversationId);
        if ( NULL == conversation )
        {
            return;
        }

        // NOTE: If the cache contains storage for this conversation, then it
        // is guaranteed to have an array to contain incoming invite codes.
        GPrimitive incoming = conversation->get(CoreFactory::createString("incoming"));
        remove(incoming, code);

        // If the size of the incoming invite code array is now zero AND there is no
        // outgoing invite code, we can delete the entire entry for this conversation.
        if (( incoming->size() == 0 ) && ( NULL == conversation->get(CoreFactory::createString("outgoing")) ))
        {
            _cache->remove(conversationId);
        }

        // Save the cache to persisted storage.
        _storage->save(_cache);
    }

    /**
     * Determines whether or not the conversation with the specified ID has an outgoing
     * ticket associated with it.
     *
     * @param conversationId The conversation ID to inspect.
     * @returns true if there is an outgoing ticket, false otherwise.
     */
    public: bool hasOutgoingTicket(const GString& conversationId)
    {
        // Get the invite code of the outgoing ticket, if one exists. If not, exit now.
        GString code = getOutgoingInviteCode(conversationId);
        if ( NULL == code )
        {
            return false;
        }

        // An outgoing ticket was found.
        return true;
    }

    /**
     * Determines whether or not the conversation with the specified ID has any incoming
     * tickets associated with it.
     *
     * @param conversationId The conversation ID to inspect.
     * @returns true if there is at least one incoming ticket, false otherwise.
     */
    public: bool hasIncomingTickets(const GString& conversationId)
    {
        // Get the invite codes of the incoming tickets, if any exist. If not, exit now.
        GPrimitive codes = getIncomingInviteCodes(conversationId);
        if (( NULL == codes ) || ( 0 == codes->size() ))
        {
            return false;
        }

        // At least one incoming ticket was found.
        return true;
    }

    /**
     * Gets the outgoing ticket invite code for the conversation with the specified ID if one exists.
     *
     * @param conversationId The conversation ID to inspect.
     * @returns The outgoing ticket invite code associated with the specified conversation if one
     * exists, NULL otherwise.
     */
    public: GString getOutgoingInviteCode(const GString& conversationId)
    {
        // If the conversation ID is NULL, exit now.
        if ( NULL == conversationId )
        {
            return NULL;
        }

        // Get the cached tickets for this conversation. If the cache contains no
        // data associated with this conversation, exit now.
        GPrimitive conversation = _cache->get(conversationId);
        if ( NULL == conversation )
        {
            return NULL;
        }

        // If the conversation has no entry for an outgoing ticket, exit now.
        GPrimitive outgoing = conversation->get(CoreFactory::createString("outgoing"));
        if ( NULL == outgoing )
        {
            return NULL;
        }

        // Return the ticket invite code for the outgoing ticket.
        return outgoing->getString();
    }

    /**
     * Gets the list of incoming invite codes for the specified conversation ID if any exist.
     *
     * @param conversationId The conversation ID to inspect.
     * @returns The GPrimitive array of incoming ticket invite codes associated with the specified
     * conversation (which may be empty), NULL if the conversation is unknown.
     */
    public: GPrimitive getIncomingInviteCodes(const GString& conversationId)
    {
        // If the conversation ID is NULL, exit now.
        if ( NULL == conversationId )
        {
            return NULL;
        }

        // Get the cached tickets for this conversation. If the cache contains no
        // data associated with this conversation, exit now.
        GPrimitive conversation = _cache->get(conversationId);
        if ( NULL == conversation )
        {
            return NULL;
        }

        // NOTE: This will never return NULL, but may return an empty GPrimitive array.
        return conversation->get(CoreFactory::createString("incoming"));
    }

    /**
     * Gets the outgoing ticket for the specified invite code. This is a helper whose
     * functionality is readily available via the Client API as well.
     *
     * @param code The invite code of the outgoing ticket to retrieve.
     * @returns The ticket object if found, NULL otherwise.
     */
    public: GTicket getOutgoingTicket(const GString& code)
    {
        // If the invite code is NULL, exit now.
        if ( NULL == code )
        {
            return NULL;
        }

        // If no Client API instance has been attached, or if that instance has
        // either not been started or has not completed its sync with the server,
        // exit now.
        if (( NULL == _glympse ) || !_glympse->isStarted() || !_glympse->getHistoryManager()->isSynced() )
        {
            return NULL;
        }

        // Attempt to lookup the ticket by its invite code.
        return _glympse->getHistoryManager()->findTicketByInviteCode(code);
    }

    /**
     * Gets the incoming ticket for the specified invite code. This is a helper whose
     * functionality is readily available via the Client API as well.
     *
     * @param code The invite code of the incoming ticket to retrieve.
     * @returns The ticket object if found, NULL otherwise.
     */
    public: GTicket getIncomingTicket(const GString& code)
    {
        // If the invite code is NULL, exit now.
        if ( NULL == code )
        {
            return NULL;
        }

        // If no Client API instance has been attached, or if that instance has
        // not been started, exit now.
        if (( NULL == _glympse ) || !_glympse->isStarted() )
        {
            return NULL;
        }

        // Attempt to lookup the ticket by its invite code.
        return _glympse->getUserManager()->findTicketByInviteCode(code);
    }

    /**
     * Private members
     */

    /**
     * Instance of Glympse API platform.
     */
    private: GGlympse _glympse;

    /**
     * Storage used to persist the mappings.
     */
    private: GStorageUnit _storage;

    /**
     * In-memory cache of ticket mappings.
     */
    private: GPrimitive _cache;

    /**
     * A helper to remove a given value from a GPrimitive array.
     *
     * @param array The GPrimitive array from which to remove the value.
     * @param value The value to remove.
     */
    private: void remove(GPrimitive array, GString value)
    {
        int count = array->size();
        for ( int index = 0; index < count ; index++ )
        {
            // For our purposes, we assume that a given value only exists in the array
            // at most one time so once we find it, remove it and bail out.
            if ( value->equals(array->getString(index)) )
            {
                array->remove(index);
                break;
            }
        }
    }
};

}
}

#endif // !CONVERSATIONHELPER_H__TOOLBOX__GLYMPSE__
