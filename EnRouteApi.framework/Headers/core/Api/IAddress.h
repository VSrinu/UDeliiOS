//------------------------------------------------------------------------------
//
// Copyright (c) 2017 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IADDRESS_H__GLYMPSE__
#define IADDRESS_H__GLYMPSE__

namespace Glympse
{
    
/**
 * Encapsulates a real world physical address.
 */
/*O*public**/ struct IAddress : public ICommon
{
    /**
     * Get Address Line 1.
     */
    public: virtual GString getLine1() = 0;
    
    /**
     * Get Address Line 2.
     */
    public: virtual GString getLine2() = 0;
    
    /**
     * Get City.
     */
    public: virtual GString getCity() = 0;
    
    /**
     * Get State.
     */
    public: virtual GString getState() = 0;
    
    /**
     * Get Zip Code.
     */
    public: virtual GString getZip() = 0;
    
    /**
     * Get Country.
     */
    public: virtual GString getCountry() = 0;
};

/*C*/typedef O< IAddress > GAddress;/**/
    
}

#endif // !IADDRESS_H__GLYMPSE__
