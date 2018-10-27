//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IPERSISTABLE_H__GLYMPSE__
#define IPERSISTABLE_H__GLYMPSE__

namespace Glympse 
{
    
/**
 * The IPersistable interface declares the two methods that a class must implement so that 
 * instances of that class can be encoded and decoded. This capability provides the basis 
 * for archiving (where objects and other structures are stored on disk) 
 * and distribution (where objects are copied to different address spaces).
 */
/*O*public**/ struct IPersistable : public virtual ICommon
{
    /**
     * Encodes the receiver using a given archiver.
     *
     * @param encoder An archiver object.
     * @param mode Encoding mode is propagated through the entire hierarchy of objects 
     * providing caller with a chance to control the process.
     */
    public: virtual void encode(const GPrimitive& encoder, int32 mode) = 0;

    /**
     * Initializes an object from data in a given unarchiver.
     * Decoding mode is not propagated. The method should pick up everything it finds. 
     */
    public: virtual void decode(const GPrimitive& decoder) = 0;
};
    
/*C*/typedef O< IPersistable > GPersistable;/**/

}

#endif // !IPERSISTABLE_H__GLYMPSE__
