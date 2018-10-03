//------------------------------------------------------------------------------
//
// Copyright (c) 2015 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IMAP_H__GLYMPSE__
#define IMAP_H__GLYMPSE__

namespace Glympse
{
    
/*C*/
template< class K, class V > struct IMap;
// Smart pointer wrapper over IMap.
template< class K, class V > class GMap
{
    private: GMap();
    public: typedef O< IMap< K, V > > ptr;
};
/**/

/*C*/template< class K, class V > struct IMap : public ICommon/**/
/*J*public interface GMap<K, V> extends GCommon**/
/*S*public interface GMap<K, V> : GCommon, IReadOnlyDictionary<K, Object>**/
{
    public: virtual V get(const K& key) = 0;
        
    public: virtual bool containsKey(const K& key) = 0;
        
    public: virtual bool containsValue(const V& value) = 0;

    public: virtual typename GEnumeration<K>::ptr keys() = 0;
        
    public: virtual int32 size() = 0;
};

}

#endif // !IMAP_H__GLYMPSE__
