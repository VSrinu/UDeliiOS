//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyPrimitive : GlyCommon< GlyComparable >

- (int)type;

- (BOOL)isArray;

- (BOOL)isObject;

- (BOOL)isDouble;

- (BOOL)isLong;

- (BOOL)isBool;

- (BOOL)isString;

- (BOOL)isNull;

- (int)size;

- (GlyPrimitive*)clone;

- (BOOL)merge:(GlyPrimitive*)from overrideTarget:(BOOL)overrideTarget;

- (double)getDouble;

- (long long int)getLong;

- (BOOL)getBool;

- (NSString*)getString;

- (GlyPrimitive*)getWithNSString:(NSString*)key;

- (double)getDoubleWithNSString:(NSString*)key;

- (long long int)getLongWithNSString:(NSString*)key;

- (BOOL)getBoolWithNSString:(NSString*)key;

- (NSString*)getStringWithNSString:(NSString*)key;

- (BOOL)hasKey:(NSString*)key;

- (GlyArray<GlyPrimitive*>*)getArray;

- (GlyPrimitive*)getWithInt:(int)index;

- (double)getDoubleWithInt:(int)index;

- (long long int)getLongWithInt:(int)index;

- (BOOL)getBoolWithInt:(int)index;

- (NSString*)getStringWithInt:(int)index;

- (void)setWithDouble:(double)value;

- (void)setWithLongLongInt:(long long int)value;

- (void)setWithBool:(BOOL)value;

- (void)setWithNSString:(NSString*)value;

- (void)setNull;

- (void)setArray;

- (void)setObject;

- (void)putWithNSString:(NSString*)key withGlyPrimitive:(GlyPrimitive*)value;

- (void)putWithNSString:(NSString*)key withDouble:(double)value;

- (void)putWithNSString:(NSString*)key withLongLongInt:(long long int)value;

- (void)putWithNSString:(NSString*)key withBool:(BOOL)value;

- (void)putWithNSString:(NSString*)key withNSString:(NSString*)value;

- (void)putNullWithNSString:(NSString*)key;

- (void)removeWithNSString:(NSString*)key;

- (void)putWithGlyPrimitive:(GlyPrimitive*)value;

- (void)putWithDouble:(double)value;

- (void)putWithLongLongInt:(long long int)value;

- (void)putWithBool:(BOOL)value;

- (void)putWithNSString:(NSString*)value;

- (void)insert:(int)index value:(GlyPrimitive*)value;

- (void)putWithInt:(int)index withGlyPrimitive:(GlyPrimitive*)value;

- (void)putWithInt:(int)index withDouble:(double)value;

- (void)putWithInt:(int)index withLongLongInt:(long long int)value;

- (void)putWithInt:(int)index withBool:(BOOL)value;

- (void)putWithInt:(int)index withNSString:(NSString*)value;

- (void)putNullWithInt:(int)index;

- (void)removeWithInt:(int)index;

- (void)removeWithGlyPrimitive:(GlyPrimitive*)value;

@end