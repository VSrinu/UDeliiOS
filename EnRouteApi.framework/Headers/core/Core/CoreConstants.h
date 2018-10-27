//------------------------------------------------------------------------------
//
// Copyright (c) Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef CORECONSTANTS_H__GLYMPSE__
#define CORECONSTANTS_H__GLYMPSE__

namespace Glympse 
{
 
/**
 * Basic enumerations belonging to Core layer. 
 */
/*O*public**/ class CoreConstants
{
    /**
     * @name Primitive Types
     *
     * Enumeration of all types supported by IPrimitive object. 
     */

    public: static const int32 PRIMITIVE_TYPE_ARRAY         = 0x00000001;
    public: static const int32 PRIMITIVE_TYPE_OBJECT        = 0x00000002;
    public: static const int32 PRIMITIVE_TYPE_DOUBLE        = 0x00000004;
    public: static const int32 PRIMITIVE_TYPE_LONG          = 0x00000008;
    public: static const int32 PRIMITIVE_TYPE_BOOLEAN       = 0x00000010;
    public: static const int32 PRIMITIVE_TYPE_STRING        = 0x00000020;
    public: static const int32 PRIMITIVE_TYPE_NULL          = 0x00000040;

    /**
     * @name Location Provider States
     *
     * Location provider changes its internal state between one of these values.
     */
    
    public: static const int32 LOCATION_STATE_NOT_DETERMINED  = 1;
    public: static const int32 LOCATION_STATE_DENIED          = 2;
    public: static const int32 LOCATION_STATE_ACQUIRED        = 3;
    public: static const int32 LOCATION_STATE_ERROR           = 4;
    
    /**
     * @name Log Levels
     * 
     * Log level specifies the level of details of log messages.
     * Log levels are ordered from the most informative INFO to the least informative CRITICAL.
     * Log levels are applied through IGlympse#overrideLoggingLevels().
     */
    
    public: static const int32 INFO         = 1;
    public: static const int32 DUMP         = 2;
    public: static const int32 NOTICE       = 3;
    public: static const int32 WARNING      = 4;
    public: static const int32 ERROR        = 5;
    public: static const int32 CRITICAL     = 6;
    public: static const int32 NONE         = 7;
    
    /**
     * @name Location Profiles
     *
     * The list of all supported location profiles on the system.
     */
    
    /**
     * Indentifies the case, when profile is not set. 
     */
    public: static const int32 LOCATION_PROFILE_NOT_SET                 = -1;
    
    /**
     * Application is running in the background without active outgoing tickets.
     */
    public: static const int32 LOCATION_PROFILE_NO_ACTIVE_BACKGROUND    = 0;
    
    /**
     * Application is running in the foreground without active outgoing tickets.
     */
    public: static const int32 LOCATION_PROFILE_NO_ACTIVE_FOREGROUND    = 1;
    
    /**
     * Application is running with active outgoing tickets, but nobody is watching.
     */
    public: static const int32 LOCATION_PROFILE_ACTIVE_NOT_WATCHED      = 2;

    /**
     * Application is running with active outgoing tickets and somebody is watching.
     */
    public: static const int32 LOCATION_PROFILE_ACTIVE_IS_WATCHED       = 3;
    
    /**
     * Total amount of profiles. 
     */
    public: static const int32 LOCATION_PROFILES_COUNT                  = 4;
    
    /**
     * @name Location Sources
     *
     * The list of supported location sources.
     */

    public: static const int32 LOCATION_SOURCE_NETWORK  = 0x00000001;
    public: static const int32 LOCATION_SOURCE_GPS      = 0x00000002;
    public: static const int32 LOCATION_SOURCE_PASSIVE  = 0x00000004;
    public: static const int32 LOCATION_SOURCE_ALL
        = LOCATION_SOURCE_NETWORK
        | LOCATION_SOURCE_GPS;
    
    /**
     * @name Location Modes
     *
     * The list of modes supported by location manager (and applied to location providers).
     */
    
    /**
     * Enables location provider.
     */
    public: static const int32 LOCATION_MODE_ENABLED    = 0;
    
    /**
     * Disables location provider.
     */ 
    public: static const int32 LOCATION_MODE_DISABLED   = 1;
    
    /**
     * @name Location Priority
     *
     * Priority identifies how aggressive application wants to be in receiving location updates.
     */
    
    public: static const int32 LOCATION_PRIORITY_HIGH_ACCURACY               = 100;
    public: static const int32 LOCATION_PRIORITY_BALANCED_POWER_ACCURACY     = 102;
    public: static const int32 LOCATION_PRIORITY_NO_POWER                    = 105;
    
    /**
     * @name Geofence Transitions
     *
     * Defines the direction of geofence transition.
     */
    
    public: static const int32 GEOFENCE_TRANSITION_ENTER    = 0x1;
    public: static const int32 GEOFENCE_TRANSITION_EXIT     = 0x2;
    
    /**
     * @name ETA Transitions
     *
     * Defines the direction of eta transition.
     */
    
    public: static const int32 ETA_TRANSITION_DROPS_BELOW    = 0x1;
    public: static const int32 ETA_TRANSITION_RISES_ABOVE    = 0x2;
    
    /**
     * @name Push States
     *
     * Represents the status of push notification availability.
     */
    
    public: static const int32 PUSH_AVAILABILITY_UNKNOWN       = 1;
    public: static const int32 PUSH_AVAILABILITY_UNAVAILABLE   = 2;
    public: static const int32 PUSH_AVAILABILITY_AVAILABLE     = 3;
    public: static const int32 PUSH_AVAILABILITY_DENIED        = 4;

    /**
     * @name Drawable Scale Types
     *
     * Scale type defines the way image gets shrunk when resized.
     */
    
    /**
     * SCALE_EXACT means to scale the image to exactly the specified size.
     * If the user passed in SCALE_EXACT, or the image size is already exactly
     * what the caller is asking for, then do nothing.
     */
    public: static const int32 DRAWABLE_SCALE_EXACT           = 0;
    
    /**
     * SCALE_FIT_OR_SMALLER is similar to SCALE_FIT, except that if the
     * image is already smaller than the width *and* height passed in, then
     * we don't do any scaling at all.
     */
    public: static const int32 DRAWABLE_SCALE_FIT_OR_SMALLER  = 1;
    
    /**
     * SCALE_FIT means to scale the image up or down so that the image
     * perfectly fits within the width/height while keeping the aspect ratio.
     * Either the new width will exactly match the width passed in and the
     * the new height will be <= the height passed in, or vice versa.
     */
    public: static const int32 DRAWABLE_SCALE_FIT             = 2;
    
    /**
     * SCALE_FILL_OR_SMALLER is similar to SCALE_FILL, except that if the
     * image is already smaller than the width *or* height passed in, then
     * we don't do any scaling at all.
     */
    public: static const int32 DRAWABLE_SCALE_FILL_OR_SMALLER = 3;
    
    /**
     * SCALE_FILL means to scale the image up or down so that the image
     * completely fills the entire width/height while keeping the aspect ratio.
     * Either the new width will exactly match the width passed in and the
     * the new height will be >= the height passed in, or vice versa.
     */
    public: static const int32 DRAWABLE_SCALE_FILL            = 4;
    
    /**
     * @name Drawable Compression Types
     *
     * Compression type defines the format used for image compression.
     */
    
    /**
     * JPEG compression method is used.
     */
    public: static const int32 DRAWABLE_COMPRESS_JPG = 0;
    
    /**
     * PNG compression method is used.
     */
    public: static const int32 DRAWABLE_COMPRESS_PNG = 1;
    
    
    /**
     * @name Device Activities
     *
     * The detected activity of the device.
     */
    
    /**
     * Device activity cannot be recognized.
     */
    public: static const int32 ACTIVITY_UNKNOWN         = 0;
    
    /**
     * The device is in a vehicle, such as a car.
     */
    public: static const int32 ACTIVITY_IN_VEHICLE      = 1;
    
    /**
     * The device is on a bicycle.
     */
    public: static const int32 ACTIVITY_ON_BICYCLE      = 2;
    
    /**
     * The device is on a user who is walking or running.
     */
    public: static const int32 ACTIVITY_ON_FOOT         = 3;
    
    /**
     * The device is still (not moving).
     */
    public: static const int32 ACTIVITY_STILL           = 4;
    
    /**
     * The device angle relative to gravity changed significantly.
     */
    public: static const int32 ACTIVITY_TILTING         = 5;

    /**
     * @name Http Methods
     * 
     * Valid HTTP methods that can be used.
     */

    /**
     * Use whatever default method is preferred.
     */
    public: static const int32 HTTP_METHOD_DEFAULT = 0;

    /**
     * Use HTTP GET method.
     */
    public: static const int32 HTTP_METHOD_GET     = 1;

    /**
     * Use HTTP POST method.
     */
    public: static const int32 HTTP_METHOD_POST     = 2;

    /**
     * Use HTTP PUT method.
     */
    public: static const int32 HTTP_METHOD_PUT      = 3;

    /**
     * Use HTTP DELETE method.
     */
    public: static const int32 HTTP_METHOD_DELETE   = 4;
};
    
}

#endif // !CORECONSTANTS_H__GLYMPSE__
