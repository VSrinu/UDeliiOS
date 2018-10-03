//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyGlympseTools : NSObject
{
}

+ (NSString*)inviteTypeEnumToString:(int)type;

+ (int)inviteTypeStringToEnum:(NSString*)type;

+ (int)guessInviteType:(NSString*)address;

+ (NSString*)ticketStateEnumToString:(int)state;

+ (int)ticketStateStringToEnum:(NSString*)state;

@end