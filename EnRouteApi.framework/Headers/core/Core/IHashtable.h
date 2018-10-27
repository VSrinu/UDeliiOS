//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IHASHTABLE_H__GLYMPSE__
#define IHASHTABLE_H__GLYMPSE__

namespace Glympse 
{

template< class K, class V > struct IHashtable : public IMap< K, V >
{
    public: virtual void put(const K& key, const V& value) = 0;
             
    public: virtual void remove(const K& key) = 0;
    
    public: virtual void clear() = 0;
};
    
template< class K, class V > class GHashtable
{
    private: GHashtable();
    public: typedef O< IHashtable< K, V > > ptr;
};
    
}

#endif // !IHASHTABLE_H__GLYMPSE__
