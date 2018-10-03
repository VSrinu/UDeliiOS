//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyDiagnosticsCollector : GlyCommon

- (void)logEvent:(NSString*)type code:(NSString*)code app:(NSString*)app cluster:(NSString*)cluster data:(GlyPrimitive*)data forceUpload:(BOOL)forceUpload;

- (void)logItem:(GlyPrimitive*)item forceUpload:(BOOL)forceUpload;

@end