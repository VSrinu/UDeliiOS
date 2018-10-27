//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyCardType : GlyCommon

- (NSString*)getId;

- (NSString*)getName;

- (NSString*)getCategory;

- (NSString*)getDescription;

- (GlyArray<GlyPrimitive*>*)getNotifications;

- (GlyPrimitive*)findNotificationByType:(NSString*)type;

@end