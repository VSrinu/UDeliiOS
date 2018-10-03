//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyPairingManager : GlyCommon< GlyEventSink >

- (BOOL)claimPairingCode:(NSString*)code;

@end