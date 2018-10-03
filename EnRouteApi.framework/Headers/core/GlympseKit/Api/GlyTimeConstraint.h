//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyTimeConstraint : GlyCommon< GlyPersistable >

- (BOOL)validateWithLongLongInt:(long long int)time;

- (BOOL)validate;

@end