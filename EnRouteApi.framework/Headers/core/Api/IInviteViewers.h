//------------------------------------------------------------------------------
//
// Copyright (c) 2017 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IINVITEVIEWERS_H__GLYMPSE__
#define IINVITEVIEWERS_H__GLYMPSE__

namespace Glympse
{
    
/**
 * Maintains a collection of invite viewers.
 *
 * Corresponding events are fired when the collection is modified. 
 * See GE::LISTENER_INVITE_VIEWERS for details.
 */
/*O*public**/ struct IInviteViewers : public IEventSink
{
    /**
     * Returns the list of invite viewers.
     *
     * @return The list of invite viewers.
     */
    public: virtual GArray<GInviteViewer>::ptr getViewers() = 0;
    
    /**
     * Returns indexed collection of invite viewers with user ID being its key.
     *
     * @return Indexed collection of invite viewers.
     */
    public: virtual GMap<GString, GInviteViewer>::ptr getViewersIndex() = 0;
};
    
/*C*/typedef O< IInviteViewers > GInviteViewers;/**/
    
}

#endif // !IINVITEVIEWERS_H__GLYMPSE__
