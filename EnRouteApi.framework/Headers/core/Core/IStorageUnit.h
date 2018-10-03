//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ISTORAGEUNIT_H__GLYMPSE__
#define ISTORAGEUNIT_H__GLYMPSE__

namespace Glympse 
{

/**
 * Represents a unit of disk-backed storage on the device.
 */
/*O*public**/ struct IStorageUnit : public ICommon
{
    public: virtual void save(const GPrimitive& data) = 0;

    public: virtual GPrimitive load() = 0;

    public: virtual void remove() = 0;
};

/*C*/typedef O< IStorageUnit > GStorageUnit;/**/

}

#endif // !ISTORAGEUNIT_H__GLYMPSE__
