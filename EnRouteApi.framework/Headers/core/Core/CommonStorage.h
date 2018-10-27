//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef COMMONSTORAGE_H__GLYMPSE__
#define COMMONSTORAGE_H__GLYMPSE__

namespace Glympse
{
    
/**
 * The purpose of this storage helper is to avoid the need in virtual inheritance
 * in client side code. This allows multiple inheritance from Common<T> without the
 * need to specify "virtual" keyword, as Common is already derived from CommonStorage
 * virtually.
 */
class CommonStorage
{
    /**
     * Our private ref count.
     */
    protected: int32 _ref;
    
    /**
     * A number of external referrers associated with the attached object.
     */
    protected: int32 _holders;
    
    /**
     * Arbitrary object attached externally.
     */
    protected: GCommon _attachedObject;
    
    protected: CommonStorage()
        : _ref(1)
        , _holders(0)
        , _attachedObject()
    {
    }
    
    protected: inline void attachObject(const GCommon& obj)
    {
        _attachedObject = obj;
    }
    
    protected: inline GCommon extractObject()
    {
        return _attachedObject;
    }
};
    
}

#endif // !COMMONSTORAGE_H__GLYMPSE__
