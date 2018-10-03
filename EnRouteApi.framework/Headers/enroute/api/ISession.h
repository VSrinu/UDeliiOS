//------------------------------------------------------------------------------
//
// Copyright (c) 2015 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ISESSION_H__ENROUTE__GLYMPSE__
#define ISESSION_H__ENROUTE__GLYMPSE__

namespace Glympse
{
namespace EnRoute
{
    
/*O*public**/ struct ISession : public ICommon
{
    public: virtual int64 getId() = 0;
    
    public: virtual int64 getCreatedTime() = 0;
    
    public: virtual GString getDescription() = 0;
    
    public: virtual GArray<GTask>::ptr getTasks() = 0;
    
    /**
     * Returns current active task
     */
    public: virtual GTask getActiveTask() = 0;
    
    /**
     * Returns the index of the current active task
     */
    public: virtual int32 getActiveTaskIndex() = 0;
    
    public: virtual int32 getState() = 0;

    public: virtual int64 getStartTime() = 0;

    public: virtual int64 getOrgId() = 0;

    public: virtual int64 getAgentId() = 0;

    public: virtual int64 getOperationId() = 0;

    public: virtual GOperation getOperation() = 0;

    public: virtual int32 getCompletionReason() = 0;

};

/*C*/typedef O<ISession> GSession;/**/
    
}
}

#endif // !ISESSION_H__ENROUTE__GLYMPSE__
