//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IDATAEVENT_H__GLYMPSE__
#define IDATAEVENT_H__GLYMPSE__

namespace Glympse 
{
    
/**
 * The class to encapsulate data passed along with GE::TICKET_DATA_APPENDED event. 
 */
/*O*public**/ struct IDataEvent : public ICommon
{
    public: virtual GTicket getTicket() = 0;    
        
    public: virtual GArray<GDataRow>::ptr getProperties() = 0;
};
    
/*C*/typedef O< IDataEvent > GDataEvent;/**/
    
}

#endif // !IDATAEVENT_H__GLYMPSE__
