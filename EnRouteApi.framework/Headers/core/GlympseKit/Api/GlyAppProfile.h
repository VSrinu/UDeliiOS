//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyAppProfile : GlyCommon< GlyComparable,GlyPersistable >

- (NSString*)getId;

- (NSString*)getName;

- (GlyImage*)getIcon;

@end