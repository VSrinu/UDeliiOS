//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@protocol GlySmsListener< NSObject >

- (void)complete:(BOOL)success code:(int)code result:(NSString*)result data:(GlyCommon*)data;

- (void)serviceNoLongerAvailable;

@end