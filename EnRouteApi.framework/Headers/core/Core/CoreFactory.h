//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef COREFACTORY_H__GLYMPSE__
#define COREFACTORY_H__GLYMPSE__

namespace Glympse 
{
    
/**
 * The CoreFactory class provides factory methods for constructing all API primitives.
 */
class CoreFactory
{
    private: CoreFactory();
    
    /**
     * Constructs string object.
     */
    public: static GString createString(const char* value);   
    
    /**
     * Constructs string object.
     */
    public: static GString createString(const char* value, int32 length);
    
    /**
     * Creates string builder object with the specified capacity.
     *
     * @param capacity The initial capacity to use.
     * @return String builder object.
     */
    public: static GStringBuilder createStringBuilder(int capacity);

    /**
     * Constructs a vector object.
     */
    public: static GVector<GCommonObj>::ptr createVector();
    
    /**
     * Constructs a linked list object.
     */
    public: static GLinkedList<GCommonObj>::ptr createLinkedList();
    
    /**
     * Constructs a hashtable object.
     */
    public: static GHashtable<GCommonObj, GCommonObj>::ptr createHashtable();
    
    /**
     * Constructs a storage object.
     */
    public: static GStorageUnit createStorage(const GCommonObj& context, const GString& name);

    /**
     * Constructs Empty GDrawable .
     */
    public: static GDrawable createDrawable();

    /**
     * Constructs GDrawable from platform specific image.
     */
    public: static GDrawable createDrawable(void* image);
    
    /**
     * Constructs GDrawable from a graphic file.
     *
     * @note It is not recommended to call this method from UI thread as it loads (and potentially resizes) 
     * image synchronously. It is preferable to perform all I/O operations from background.
     *
     * @param path A path to a file that contains the graphic.
     * @param rotation The degrees of clockwise rotation that should be applied to the image.
     */
    public: static GDrawable createDrawable(const GString& path, int32 rotation);
    
    /**
     * Constructs uninitialized primitive object of specific type.
     * It might be useful for array and object primitives
     * (CC::PRIMITIVE_TYPE_ARRAY, CC::PRIMITIVE_TYPE_OBJECT).
     *
     * @param type Primitive type. See CC for details. 
     */
    public: static GPrimitive createPrimitive(int32 type);
    
    /**
     * Constructs initialized primitive object of CC::PRIMITIVE_TYPE_DOUBLE type.
     */
    public: static GPrimitive createPrimitive(double value);    
    
    /**
     * Constructs initialized primitive object of CC::PRIMITIVE_TYPE_LONG type.
     */
    public: static GPrimitive createPrimitive(int64 value);        
    
    /**
     * Constructs initialized primitive object of CC::PRIMITIVE_TYPE_BOOL type.
     */
    public: static GPrimitive createPrimitive(bool value);            
    
    /**
     * Constructs initialized primitive object of CC::PRIMITIVE_TYPE_STRING type.
     */
    public: static GPrimitive createPrimitive(const GString& value);  
    
    /**
     * Constructs initialized primitive object of CC::PRIMITIVE_TYPE_NULL type.
     */
    public: static GPrimitive createPrimitive();
    
    /**
     * Creates builder object for creating custom location profiles.
     *
     * @param profileId The id of the profile you would like the builder to create. See CC::LOCATION_PROFILE_* for 
     * the list of profile ids.
     * @return Location profile builder object.
     */
    public: static GLocationProfileBuilder createLocationProfileBuilder(int32 profileId);
    
    /**
     * Creates new location object from location data.
     *
     * time, latitude and longitude fields must be specified. Any other field can be set to Float.NaN.
     *
     * @param time Location timestamp (milliseconds since 1/1/1970). It is preferable to use server time here.
     * @param latitude Location latitude in degrees.
     * @param longitude Location longitude in degrees.
     * @param speed Location speed in meters per second over ground. Speed must be positive.
     * @param bearing Location bearing in degrees. Bearing is the horizontal direction of travel of this device,
     * and is not related to the device orientation. The input must be in range [0.0, 360.0].
     * @param altitude Location altitude in meters above sea level.
     * @param haccuracy Horizontal accuracy of this location in meters.
     * @param vaccuracy Vertical accuracy of this location in meters.
     */
    public: static GLocation createLocation(int64 time, double latitude, double longitude,
        float speed, float bearing, float altitude, float haccuracy, float vaccuracy);
    
    /**
     * Creates new location object from location data.
     *
     * @param latitude Location latitude in degrees.
     * @param longitude Location longitude in degrees.
     */
    public: static GLocation createLocation(double latitude, double longitude);
    
    /**
     * Constructs initialized GLong object with the specified value
     */
    public: static GLong createLong(int64 val);
    
    /**
     * Creates new region object. 
     *
     * @param latitude The latitude of the central point of the alert region.
     * @param longitude The longitude of the central point of the alert region.
     * @param radius The radius of the central point of the alert region, in meters.
     * @param rid Unique identifier of a region.
     * @return Region object.
     */
    public: static GRegion createRegion(double latitude, double longitude, double radius, const GString& rid);
    
    /**
     * Creates default location provider.
     */
    public: static GLocationProvider createLocationProvider(const GCommonObj& context);
    
    /**
     * Returns client operating system name. e.g. "ios" or "android"
     */
    public: static GString getOsName();
    
    /**
     * Explicitly enables or disables this library's registration of signal handlers. Enabled by default.
     *
     * Must be called before platform is instantiated (GlympseFactory::createGlympse()), or it has no effect.
     */
    public: static void enableSignalHandlers(bool enable);
    
    /**
     * Discover whether signal handlers were successfully enabled or disabled.
     */
    public: static bool areSignalHandlersEnabled();
};
    
}

#endif // !COREFACTORY_H__GLYMPSE__
