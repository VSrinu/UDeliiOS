//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyCommon : NSObject

- (instancetype)init NS_UNAVAILABLE;

#ifdef __cplusplus

+ (instancetype)bind:(const Glympse::GCommon &)object;

- (id)initWithCommon:(const Glympse::GCommon &)object;

- (id)initAndBindWithCommon:(const Glympse::GCommon &)object;

- (Glympse::GCommon)object;

#endif

- (int)hashCode;

- (BOOL)equals:(GlyCommon *)gocCommon;

- (NSString *)toString;

@end
