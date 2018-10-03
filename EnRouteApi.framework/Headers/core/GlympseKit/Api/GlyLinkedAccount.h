//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyLinkedAccount : GlyCommon

- (NSString*)getType;

- (int)getState;

- (int)getStatus;

- (NSString*)getId;

- (NSString*)getUserName;

- (NSString*)getDisplayName;

- (int)getLogin;

- (GlyServerError*)getError;

@end