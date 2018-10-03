//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyApiStatus : GlyCommon

- (BOOL)checkStatus:(id<GlyApiStatusListener>)listener;

@end