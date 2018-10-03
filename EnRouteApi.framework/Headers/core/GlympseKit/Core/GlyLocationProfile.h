//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyLocationProfile : GlyCommon< GlyComparable >

- (int)getProfile;

- (int)getMode;

- (int)getSource;

- (double)getDistance;

- (double)getAccuracy;

- (int)getFrequency;

- (int)getPriority;

- (int)getActivity;

- (BOOL)isAutoPauseEnabled;

- (BOOL)isSignificantLocationChangeMonitoringEnabled;

@end