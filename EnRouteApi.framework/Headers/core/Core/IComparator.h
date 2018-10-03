//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ICOMPARATOR_H__GLYMPSE__
#define ICOMPARATOR_H__GLYMPSE__

namespace Glympse 
{
    
template< class T > struct IComparator : public ICommon
{
    /**
     * Returns
     *     <0 if the object 1 is less than    object 2
     *      0 if the object 1 is equal to     object 2
     *     >0 if the object 1 is greater than object 2
     */
    public: virtual int32 compare(const T& ob1, const T& obj2) = 0;
};
    
template< class T > class GComparator
{       
    private: GComparator();
    public: typedef O< IComparator< T > > ptr;
};
    
}

#endif // !ICOMPARATOR_H__GLYMPSE__
