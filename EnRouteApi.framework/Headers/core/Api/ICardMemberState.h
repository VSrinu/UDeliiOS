//------------------------------------------------------------------------------
//
// Copyright (c) 2016 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ICARDMEMBERSTATE_H__GLYMPSE__
#define ICARDMEMBERSTATE_H__GLYMPSE__

namespace Glympse
{

/**
 * Exposes card member state properties.
 */
/*O*public**/ struct ICardMemberState : public ICommon
{
    /**
     * @return time that the card member last acknowledged viewing the card. Epoch time (ms)
     */
    public: virtual int64 getLastAcknowledgeTime() = 0;
};

/*C*/typedef O< ICardMemberState > GCardMemberState;/**/
        
}

#endif // !ICARDMEMBERSTATE_H__GLYMPSE__
