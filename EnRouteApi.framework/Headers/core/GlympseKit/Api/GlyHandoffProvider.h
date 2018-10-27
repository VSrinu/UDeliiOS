//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyHandoffProvider : GlyCommon

- (BOOL)isEnabled;

- (NSString*)getProviderId;

- (BOOL)isHandoffAvailable;

- (BOOL)isForceable;

- (NSString*)getActionUri:(int)action;

- (int)getDisabledTicketFields;

- (void)allowHandoff;

- (BOOL)isHandoffAllowed;

@end