//------------------------------------------------------------------------------
//
// Copyright (c) 2016 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef HOLDER_H__GLYMPSE__
#define HOLDER_H__GLYMPSE__

namespace Glympse
{
 
/**
 * Smart pointer designed to hold a pointer to an object.
 *
 * ICommon::hold() and ICommon::unhold() methods are used to adjust state of referred object.
 */
template< class T > class Holder
{
    /**
     * A pointer to the object we are referencing.
     */
    private: T* _object;
        
    /**
     * @name Constructors
     */
    
    /**
     * This constructor just creates an empty "null reference" that can be assinged later.
     */
    public: Holder()
        : _object(NULL)
    {
    }
    
    /**
     * @name Assignment Operators
     */
    
    public: Holder<T>& operator=(const O<T>& rO)
    {
        release();
        _object = rO.operator->();
        retain();
        return *this;
    }
    public: template< class T2 > Holder<T>& operator=(const O<T2>& rO)
    {
        release();
        _object = dynamic_cast<T*>(rO.operator->());
        retain();
        return *this;
    }
    
    /**
     * @name Destructor
     */
    
    /**
     * Regardless of how we obtained the object we are pointing to, we release it when we destuct.
     */
    public: virtual ~Holder()
    {
        release();
    }
    
    /**
     * @name Member Access
     * This is how we allow access to the members of the object we are referencing.
     */
    
    T* operator->()
    {
        return _object;
    }
    T* operator->() const
    {
        return _object;
    }
    O<T> o()
    {
        _object->retain();
        return O<T>(_object);
    }
    
    /**
     * @name Internals
     */
    
    /**
     * Internal helper function to safely add a reference.
     */
    private: inline void retain()
    {
        if ( _object )
        {
            _object->hold();
        }
    }
    
    /**
     * Internal helper function to safely release a reference.
     */
    private: inline void release()
    {
        if ( _object )
        {
            _object->unhold();
            _object = NULL;
        }
    }
};
    
}

#endif // !HOLDER_H__GLYMPSE__
