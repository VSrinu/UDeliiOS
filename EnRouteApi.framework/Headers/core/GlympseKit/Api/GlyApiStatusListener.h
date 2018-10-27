//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@protocol GlyApiStatusListener< NSObject >

- (void)statusUpdated:(BOOL)available;

@end