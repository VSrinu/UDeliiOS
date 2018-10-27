//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyPhaseConfig : GlyCommon

- (BOOL)isVisible;

- (BOOL)shouldClearEta;

- (BOOL)enabledInFlow;

- (GlyArray<GlyPrimitive*>*)getMetadata;

@end