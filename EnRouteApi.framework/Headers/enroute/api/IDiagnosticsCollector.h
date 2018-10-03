//------------------------------------------------------------------------------
//
// Copyright (c) 2016 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IDIAGNOSTICSCOLLECTOR_H__ENROUTE__GLYMPSE__
#define IDIAGNOSTICSCOLLECTOR_H__ENROUTE__GLYMPSE__

namespace Glympse
{
namespace EnRoute
{
/*O*public**/ struct IDiagnosticsCollector : public ICommon
{
    public: virtual void logEvent(const GString& type, const GString& code, const GString& app, const GString& cluster, const GPrimitive& data, bool forceUpload) = 0;
    
    public: virtual void logItem(const GPrimitive& item, bool forceUpload) = 0;
};

/*C*/typedef O<IDiagnosticsCollector> GDiagnosticsCollector;/**/
    
}
}

#endif // !IDIAGNOSTICSCOLLECTOR_H__ENROUTE__GLYMPSE__
