//------------------------------------------------------------------------------
//
// Copyright (c) 2015 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IXOALISTENER_H__GLYMPSE__
#define IXOALISTENER_H__GLYMPSE__

namespace Glympse
{
    
/**
 * The listener interface determining which tickets should be affected by XoA logic.
 */
/*O*public**/ struct IXoAListener : public virtual ICommon
{
    /**
     * This listener method is invoked for each ticket the XoAManager is listening to.
     *
     * @param ticket, the ticket in question.
     * @return true, if the XoAManager should activate XoA for the given ticket.
     */
    public: virtual bool shouldMonitorTicket(const GTicket& ticket) = 0;
};

/*C*/typedef O< IXoAListener > GXoAListener;/**/
    
}

#endif // !IXOALISTENER_H__GLYMPSE__
