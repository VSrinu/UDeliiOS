//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyGroupManager : GlyCommon< GlyEventSink >

- (BOOL)isSynced;

- (BOOL)isValidGroup:(NSString*)name;

- (int)validateGroupName:(NSString*)name;

- (GlyGroup*)viewGroup:(NSString*)name;

- (GlyArray<GlyGroup*>*)getGroups;

- (GlyGroup*)findGroupByGroupId:(NSString*)groupId;

- (BOOL)anyActive;

- (int)startTracking:(GlyGroup*)group;

- (int)stopTracking:(GlyGroup*)group;

- (void)startTrackingAll;

- (void)stopTrackingAll:(BOOL)forced;

- (BOOL)anyActiveTracked;

- (BOOL)isTracking:(GlyGroup*)group;

@end