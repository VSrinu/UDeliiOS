//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IPRIMITIVE_H__GLYMPSE__
#define IPRIMITIVE_H__GLYMPSE__

namespace Glympse
{

/*C*/struct IPrimitive;
typedef O< IPrimitive > GPrimitive;/**/

/**
 * The IPrimitive interface is designed to operate with free form data structures.
 * The model behind IPrimitive conforms to JavaScript Object Notation (JSON)
 * (see http://www.ietf.org/rfc/rfc4627 for details).
 *
 * Supported primitive types are (see CC):
 * - array (PRIMITIVE_TYPE_ARRAY) - represents array of IPrimitive objects;
 * - object (PRIMITIVE_TYPE_OBJECT) - represents string hastable with value of IPrimitive type;
 * - double (PRIMITIVE_TYPE_DOUBLE) - represents value of primitive double type;
 * - long (PRIMITIVE_TYPE_LONG) - represents value of primitive long type (Glympse::int64);
 * - boolean (PRIMITIVE_TYPE_BOOL) - represents value of primitive boolean type;
 * - string (PRIMITIVE_TYPE_STRING) - represents value of primitive string type (Glympse::IString);
 * - null (PRIMITIVE_TYPE_BOOL) - indicates that object does not contain any value associated with it.
 */
/*O*public**/ struct IPrimitive : public IComparable
{
    /**
     * Common properties.
     */

    public: virtual int32 type() = 0;

    public: virtual bool isArray() = 0;

    public: virtual bool isObject() = 0;

    public: virtual bool isDouble() = 0;

    public: virtual bool isLong() = 0;

    public: virtual bool isBool() = 0;

    public: virtual bool isString() = 0;

    public: virtual bool isNull() = 0;

    public: virtual int32 size() = 0;
    
    public: virtual GPrimitive clone() = 0;

    /**
     * merge provides a mechanism for combining two primitives within the following rules.
     * If the rules are not met, the merge fails unless the overrideTarget parameter is set
     * to true and then the merge becomes a copy operation.
     *   1) For boolean string, long, double and null types only the same type may be merged in by default.
     *   2) For an array any primitive can be merged into an array and will be appended to the end of an array. Merging two arrays will append clones of each element of the "from" array.
     *   3) For object(hashtable) primitives only another object may be merged with it by default. For each key in the "from" primitive merge attempts to insert it into the target primitive according to these rules if the key already exists. If it doesn't exist, it always inserts a copy.
     */
    public: virtual bool merge(const GPrimitive& from, bool overrideTarget) = 0;

    /**
     * Value getters.
     */

    public: virtual double getDouble() = 0;

    public: virtual int64 getLong() = 0;

    public: virtual bool getBool() = 0;

    public: virtual GString getString() = 0;

    /**
     * Object getters.
     */

    public: virtual GPrimitive get(const GString& key) = 0;

    public: virtual double getDouble(const GString& key) = 0;

    public: virtual int64 getLong(const GString& key) = 0;

    public: virtual bool getBool(const GString& key) = 0;

    public: virtual GString getString(const GString& key) = 0;

    public: virtual GEnumeration<GString>::ptr getKeys() = 0;

    public: virtual bool hasKey(const GString& key) = 0;

    /**
     * Array getters.
     */

    public: virtual GArray<GPrimitive>::ptr getArray() = 0;

    public: virtual GPrimitive get(int32 index) = 0;

    public: virtual double getDouble(int32 index) = 0;

    public: virtual int64 getLong(int32 index) = 0;

    public: virtual bool getBool(int32 index) = 0;

    public: virtual GString getString(int32 index) = 0;

    /**
     * Value modifiers.
     */

    public: virtual void set(double value) = 0;

    public: virtual void set(int64 value) = 0;

    public: virtual void set(bool value) = 0;

    public: virtual void set(const GString& value) = 0;

    public: virtual void setNull() = 0;

    public: virtual void setArray() = 0;

    public: virtual void setObject() = 0;

    /**
     * Object modifiers.
     */

    public: virtual void put(const GString& key, const GPrimitive& value) = 0;

    public: virtual void put(const GString& key, double value) = 0;

    public: virtual void put(const GString& key, int64 value) = 0;

    public: virtual void put(const GString& key, bool value) = 0;

    public: virtual void put(const GString& key, const GString& value) = 0;

    public: virtual void putNull(const GString& key) = 0;

    public: virtual void remove(const GString& key) = 0;

    /**
     * Array modifiers.
     */

    public: virtual void put(const GPrimitive& value) = 0;

    public: virtual void put(double value) = 0;

    public: virtual void put(int64 value) = 0;

    public: virtual void put(bool value) = 0;

    public: virtual void put(const GString& value) = 0;

    public: virtual void insert(int32 index, const GPrimitive& value) = 0;

    public: virtual void put(int32 index, const GPrimitive& value) = 0;

    public: virtual void put(int32 index, double value) = 0;

    public: virtual void put(int32 index, int64 value) = 0;

    public: virtual void put(int32 index, bool value) = 0;

    public: virtual void put(int32 index, const GString& value) = 0;

    public: virtual void putNull(int32 index) = 0;

    public: virtual void remove(int32 index) = 0;

    public: virtual void remove(const GPrimitive& value) = 0;
    
};

}

#endif // !IPRIMITIVE_H__GLYMPSE__