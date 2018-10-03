//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@protocol GlySmsProvider< NSObject >

- (int)canDeviceSendSms;

- (BOOL)sendSms:(NSString*)address message:(NSString*)message listener:(id<GlySmsListener>)listener;

@end