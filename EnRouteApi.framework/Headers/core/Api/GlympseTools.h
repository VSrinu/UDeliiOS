//------------------------------------------------------------------------------
//
// Copyright (c) 2014 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef GLYMPSETOOLS_H__GLYMPSE__
#define GLYMPSETOOLS_H__GLYMPSE__

namespace Glympse
{

/**
 * Static helpers for manipulating various Glympse concepts.
 */
/*O*public**/ class GlympseTools
{
    /**
     * Converts invite type code into string representation.
     *
     * @param type Invite type. See GC::INVITE_TYPE_* for the list of supported types.
     * @return Invite type string or the string of "unknown" if type is not supported.
     */
    public: static GString inviteTypeEnumToString(int32 type);
    
    /**
     * Converts invite type string to one of GC::INVITE_TYPE_* constants.
     *
     * @param type Invite type string.
     * @return Invite type code or GC::INVITE_TYPE_UNKNOWN if specified type is not recognized.
     */
    public: static int32 inviteTypeStringToEnum(const GString& type);
    
    /**
     * Detects invite type (GC::INVITE_TYPE_*) by the given address.
     * Currently the following types can be detected:
     * - GC::INVITE_TYPE_SMS
     * - GC::INVITE_TYPE_EMAIL
     * - GC::INVITE_TYPE_GROUP
     *
     * @param address Invite address.
     * @return Invite type code or GC::INVITE_TYPE_UNKNOWN if specified address does not
     * look like any of supported universal addresses.
     */
    public: static int32 guessInviteType(const GString& address);

    /**
     * Converts the ticket state enum into string representation.
     *
     * @param state Ticket state. See GC::TICKET_STATE_* for the list of supported types.
     * @return Ticket state string or the string of "unknown" if the state is not supported.
     */
    public: static GString ticketStateEnumToString(int32 state);

    /**
     * Converts the ticket state string into one of GC::TICKET_STATE_* constants.
     *
     * @param state Ticket state string.
     * @return Ticket State code or TICKET_STATE_NONE if specified state is not recognized.
     */
    public: static int32 ticketStateStringToEnum(const GString& state);

};
    
}

#endif // !GLYMPSETOOLS_H__GLYMPSE__
