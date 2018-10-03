//------------------------------------------------------------------------------
//
// Copyright (c) 2014 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef CORETOOLS_H__GLYMPSE__
#define CORETOOLS_H__GLYMPSE__

namespace Glympse
{

/**
 * Basic serialization tools.
 */
class CoreTools
{
    private: CoreTools();
    
    /**
     * Converts GPrimitive into string representation.
     */
    public: static GString primitiveToString(const GPrimitive& data);
    
    /**
     * Parses JSON string into GPrimitive object.
     */
    public: static GPrimitive stringToPrimitive(const GString& json);

    /**
     * Convert http method enum to string.
     */
    public: static GString httpMethodEnumToString(int32 methodType);

    /**
     * Convert http method string to enum.
     */
    public: static int32 httpMethodStringToEnum(const GString& methodString);

    /**
     * Translates string into URL-encoded format.
     */
    public: static GString urlEncode(const GString& str);
    
    /**
     * Decodes a URL-encoded string.
     */
    public: static GString urlDecode(const GString& str);
};

}

#endif // !CORETOOLS_H__GLYMPSE__
