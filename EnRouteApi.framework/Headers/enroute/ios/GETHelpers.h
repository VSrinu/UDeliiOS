//------------------------------------------------------------------------------
//
// Copyright (c) 2014 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#import <Foundation/Foundation.h>

@interface GETHelpers : NSObject

+ (void)subscribe:(id<GETListener>)listener onManager:(const Glympse::GSource&)manager;

+ (void)unsubscribe:(id<GETListener>)listener onManager:(const Glympse::GSource&)manager;

+ (NSString*)toNSString:(const Glympse::GString&)str;

+ (Glympse::GString)toGString:(NSString*)str;

@end
