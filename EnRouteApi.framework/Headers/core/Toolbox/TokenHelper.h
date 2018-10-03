//------------------------------------------------------------------------------
//
// Copyright (c) 2014 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef TOKENHELPER_H__TOOLBOX__GLYMPSE__
#define TOKENHELPER_H__TOOLBOX__GLYMPSE__

namespace Glympse
{
namespace Toolbox
{
        
/**
 * Automates and simplifies Glympse access token acquisition.
 */
/*O*public**/ class TokenHelper
{
    /**
     * Notifies consumer when token becomes available.
     */
    public: struct ITokenListener : public ICommon
    {
        /**
         * The method is called upon successful token acquisition.
         *
         * @param accessToken Glympse access token.
         */
        public: virtual void tokenAcquired(const GString& accessToken) = 0;
        
        /**
         * The method is called if platform fails to acquire token permanently.
         */
        public: virtual void failedToAcquireToken() = 0;
    };
    /*C*/typedef O< ITokenListener > GTokenListener;/**/
    
    /**
     * Acquires Glympse token and notifies listener when it becomes available. 
     *
     * @param glympse Glympse platform instance. The platform must be started.
     * @param tokenListener Token listener.
     * @return true if token is acquired or will be acquired shortly.
     */
    public: static bool acquireToken(const GGlympse& glympse, const GTokenListener& tokenListener)
    {
        if ( ( NULL == glympse ) || !glympse->isStarted() || ( NULL == tokenListener ) )
        {
            return false;
        }

        // See if token is already available.
        GString accessToken = glympse->getAccessToken();
        if ( NULL != accessToken )
        {
            tokenListener->tokenAcquired(accessToken);
            return true;
        }
    
        // Subscribe on platform events and hope for the best.
        glympse->addListener(new TokenMonitor(tokenListener));
        return true;
    }
    
    /**
     * Helper class to wait for GE::PLATFORM_LOGIN_SUCCEEDED.
     */
    private: /*J*static**/ class TokenMonitor : public Common< IEventListener >
    {
        private: GTokenListener _tokenListener;
        
        public: TokenMonitor(const GTokenListener& tokenListener)
        {
            _tokenListener = tokenListener;
        }
    
        /**
         * @name IEventListener section
         */
            
        public: virtual void eventsOccurred(const GGlympse& glympse, int32 listener, int32 events, const GCommonObj& obj)
        {
            // Events spread by the platform.
            if ( GE::LISTENER_PLATFORM == listener )
            {
                // Platform is authenticated. This is what we are waiting for.
                if ( 0 != ( GE::PLATFORM_LOGIN_SUCCEEDED & events ) )
                {
                    // Notify listener on success.
                    GString accessToken = glympse->getAccessToken();
                    _tokenListener->tokenAcquired(accessToken);
                    
                    // Unsubscribe from platform events.
                    glympse->removeListener(Object::fromThis(this));
                }
                
                // Platform is stopped. 
                else if ( 0 != ( GE::PLATFORM_STOPPED & events ) )
                {
                    _tokenListener->failedToAcquireToken();
                }
            }
        }
    };
};
    
}
}

#endif // !TOKENHELPER_H__TOOLBOX__GLYMPSE__
