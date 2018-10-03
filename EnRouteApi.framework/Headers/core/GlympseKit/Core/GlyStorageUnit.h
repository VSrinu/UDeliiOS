//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyStorageUnit : GlyCommon

- (void)save:(GlyPrimitive*)data;

- (GlyPrimitive*)load;

- (void)remove;

@end