//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyServerError : GlyCommon

- (int)getType;

- (NSString*)getError;

- (NSObject*)getExtraParam;

- (NSString*)getErrorDetails;

@end