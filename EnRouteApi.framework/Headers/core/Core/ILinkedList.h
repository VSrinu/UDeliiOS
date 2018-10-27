//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ILINKEDLIST_H__GLYMPSE__
#define ILINKEDLIST_H__GLYMPSE__

namespace Glympse
{
    
template< class T > struct ILinkedList : public IList< T >
{
    public: virtual void addFirst(const T& o) = 0;
    
    public: virtual void addLast(const T& o) = 0;
    
    public: virtual void removeFirst() = 0;
    
    public: virtual void removeLast() = 0;
    
    public: virtual void remove(const T& o) = 0;
    
    public: virtual void clear() = 0;
    
    public: virtual bool isEmpty() = 0;
    
    public: virtual int32 size() = 0;
};
    
template< class T > class GLinkedList
{
    private: GLinkedList();
    public: typedef O< ILinkedList< T > > ptr;
};
    
}

#endif // !ILINKEDLIST_H__GLYMPSE__
