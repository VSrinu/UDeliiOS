//------------------------------------------------------------------------------
//
// Copyright (c) 2017 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IINVITEVIEWER_H__GLYMPSE__
#define IINVITEVIEWER_H__GLYMPSE__

namespace Glympse
{
    
/**
 * Incapsulates invite viewer details.
 */
/*O*public**/ struct IInviteViewer : public ICommon
{
    /**
     * Returns user ID of a viewer.
     *
     * @return User ID string.
     */
    public: virtual GString getUserId() = 0;
        
    /**
     * Returns last view time.
     *
     * @return Last view time in milliseconds, UTC.
     */
    public: virtual int64 getLastViewedTime() = 0;
};
    
/*C*/typedef O< IInviteViewer > GInviteViewer;/**/
    
}

#endif // !IINVITEVIEWER_H__GLYMPSE__
