//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IDATAROW_H__GLYMPSE__
#define IDATAROW_H__GLYMPSE__

namespace Glympse 
{
    
/**
 * Encapsulates data related to specific property. 
 */
/*O*public**/ struct IDataRow : public ICommon
{
    public: virtual int64 getTime() = 0;    
    
    public: virtual int64 getPartnerId() = 0;
    
    public: virtual GString getName() = 0;
    
    public: virtual GPrimitive getValue() = 0;
};
    
/*C*/typedef O< IDataRow > GDataRow;/**/
    
}

#endif // !IDATAROW_H__GLYMPSE__
