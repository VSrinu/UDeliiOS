//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyDataRow : GlyCommon

- (long long int)getTime;

- (long long int)getPartnerId;

- (NSString*)getName;

- (GlyPrimitive*)getValue;

@end