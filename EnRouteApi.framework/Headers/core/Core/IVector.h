//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IVECTOR_H__GLYMPSE__
#define IVECTOR_H__GLYMPSE__

namespace Glympse 
{
 
template< class T > struct IVector : public IArray< T >
{
    public: virtual void ensureCapacity(int32 capacity) = 0;    

    public: virtual void addElement(const T& o) = 0;
            
    public: virtual void setElementAt(const T& o, int32 location) = 0;
            
    public: virtual void insertElementAt(const T& o, int32 location) = 0;
            
    public: virtual bool removeElementAt(int32 index) = 0;
    
    public: virtual void removeRange(int32 start, int32 end) = 0;
 
    public: virtual bool removeElement(const T& o) = 0;

    public: virtual void removeAllElements() = 0;

    public: virtual bool contains(const T& o) = 0;

    public: virtual int32 size() = 0;

    public: virtual bool isEmpty() = 0;            

    public: virtual T elementAt(int32 index) = 0;

    public: virtual T lastElement() = 0;
    
    public: virtual void sort(const typename GComparator<T>::ptr& comparator) = 0;
};
    
template< class T > class GVector
{       
    private: GVector();
    public: typedef O< IVector< T > > ptr;
};
    
}

#endif // !IVECTOR_H__GLYMPSE__
