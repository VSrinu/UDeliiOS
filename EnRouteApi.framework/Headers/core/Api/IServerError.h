//------------------------------------------------------------------------------
//
// Copyright (c) 2013 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ISERVERERROR_H__GLYMPSE__
#define ISERVERERROR_H__GLYMPSE__

namespace Glympse 
{
    
/**
 * Provides details about errors that occur during server interactions.
 */
/*O*public**/ struct IServerError : public ICommon
{
    /**
     * Returns the type of error that occurred.
     *
     * @return An error code defined in a GC#SERVER_ERROR constant.
     */
    public: virtual int32 getType() = 0;

    /**
     * Returns the name of the error that occurred.
     *
     * @return A string describing the error.
     */
    public: virtual GString getError() = 0;

    /**
     * Returns the extra param associated with the error that occurred.
     *
     * @return An object whose type is dependent on the type of error.
     */
    public: virtual GCommonObj getExtraParam() = 0;

    /**
     * @name Debug Tools
     *
     * These tools are provided for debugging purposes only and should never be invoked from
     * production code.
     */
    
    /**
     * Returns details about the error that occurred.
     *
     * @return A string containing specifics regarding the cause of the error.
     */
    public: virtual GString getErrorDetails() = 0;
};
    
/*C*/typedef O< IServerError > GServerError;/**/
    
}

#endif // !ISERVERERROR_H__GLYMPSE__
