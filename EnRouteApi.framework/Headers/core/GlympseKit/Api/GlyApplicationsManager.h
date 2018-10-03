//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyApplicationsManager : GlyCommon< GlyEventSink >

- (GlyArray<GlyApplication*>*)getApplications;

- (BOOL)isInstalled:(GlyApplication*)application;

- (BOOL)canInstall:(GlyApplication*)application;

- (BOOL)install:(GlyApplication*)application;

- (BOOL)canSend:(GlyInvite*)invite;

@end