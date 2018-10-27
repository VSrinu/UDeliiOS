//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@protocol GlyPersistable< NSObject >

- (void)encode:(GlyPrimitive*)encoder mode:(int)mode;

- (void)decode:(GlyPrimitive*)decoder;

@end