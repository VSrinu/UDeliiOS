//------------------------------------------------------------------------------
//
// Copyright (c) 2016 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef CLASSBINDER_H__GLYMPSE__
#define CLASSBINDER_H__GLYMPSE__

namespace Glympse
{
    
class ClassBinder
{
    public: ClassBinder();
    
    public: static void init();
    
    public: static id bind(const GCommon& obj);
    
    public: static void bind(const GCommon& obj, id ido);
    
    public: static GCommon unwrap(id ido);
};
    
}

#endif // !CLASSBINDER_H__GLYMPSE__
