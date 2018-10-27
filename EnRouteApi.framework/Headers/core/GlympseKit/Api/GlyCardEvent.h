//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyCardEvent : GlyCommon

- (NSString*)getId;

- (NSString*)getType;

- (NSString*)getCardId;

- (NSString*)getCardMemberId;

- (NSString*)getUserId;

- (NSString*)getKind;

- (BOOL)isNativeKind;

- (GlyPrimitive*)getData;

- (long long int)getLastModifiedTime;

- (long long int)getCreatedTime;

@end