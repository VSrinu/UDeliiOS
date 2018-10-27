//------------------------------------------------------------------------------
//
// Copyright (c) 2013 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IPAIRINGMANAGER_H__GLYMPSE__
#define IPAIRINGMANAGER_H__GLYMPSE__

namespace Glympse
{

/**
 * Manager to allow for accounts to be shared amongst devices via a pairing code and to
 * provide events when pairing occurs.
 */
/*O*public**/ struct IPairingManager : public IEventSink
{
    /**
     * Links the currently logged in accounts via a pairing code to another device.
     *
     * Events are sent with GE::LISTENER_PAIRING. Possible events are:
     * GE::PAIRING_CODE_CLAIMED for successful pairing and GE::PAIRING_CODE_FAILED
     * for failures. Events have the claim code used for pairing sent back
     * with the event.
     *
     * @param code The pairing code from the device to be linked.
     * @return True if the request was made to the server, otherwise false.
     */
    public: virtual bool claimPairingCode(const GString& code) = 0;
};
    
/*C*/typedef O< IPairingManager > GPairingManager;/**/
    
}

#endif // !IPAIRINGMANAGER_H__GLYMPSE__
