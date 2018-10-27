//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IIMAGE_H__GLYMPSE__
#define IIMAGE_H__GLYMPSE__

namespace Glympse 
{
    
/**
 * Wraps drawable object and provides control over its life cycle.
 */
/*O*public**/ struct IImage : public IEventSink
{
    /**
     * Gets image state. See GC::IMAGE_STATE_* for more details. 
     */
    public: virtual int32 getState() = 0;
    
    /**
     * Gets URI of the image.
     * 
     * @return Image URI or NULL, if image is not initialized.
     */
    public: virtual GString getUrl() = 0;
    
    /**
     * Gets underlying drawable object.
     *
     * @return Drawable object or NULL, if drawable is not loaded or image is not initialized.
     */
    public: virtual GDrawable getDrawable() = 0;
    
    /**
     * Attempts to start loading drawable.
     *
     * GE::IMAGE_CHANGED is sent to subscribers, if image loading is succussfully scheduled. 
     * The event is spread synchronously before execution is returned to caller. 
     *
     * @return true, if loading was scheduled correctly or image is loading or already loaded.
     * false, if image is not properly initialized.
     */
    public: virtual bool load() = 0;
    
    /**
     * Frees underlying drawable object. 
     *
     * @return true, if operation completed successfully.
     * failse, if image is currently loading or is not properly initialized. 
     */
    public: virtual bool unload() = 0;
};
    
/*C*/typedef O< IImage > GImage;/**/    
    
}

#endif // !IIMAGE_H__GLYMPSE__
