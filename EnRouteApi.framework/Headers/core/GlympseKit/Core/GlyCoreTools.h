//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyCoreTools : NSObject
{
}

+ (NSString*)primitiveToString:(GlyPrimitive*)data;

+ (GlyPrimitive*)stringToPrimitive:(NSString*)json;

+ (NSString*)httpMethodEnumToString:(int)methodType;

+ (int)httpMethodStringToEnum:(NSString*)methodString;

+ (NSString*)urlEncode:(NSString*)str;

+ (NSString*)urlDecode:(NSString*)str;

@end