//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse. All rights reserved.
//
//------------------------------------------------------------------------------


@interface GlyArray<__covariant ObjectType> : GlyCommon< NSFastEnumeration >

- (NSInteger)count;

- (ObjectType)objectAtIndex:(NSInteger)index;
- (ObjectType)objectAtIndexedSubscript:(NSInteger)index;

@end
