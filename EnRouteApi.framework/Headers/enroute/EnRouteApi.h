//------------------------------------------------------------------------------
//
// Copyright (c) 2014 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef TRACKINGAPI_H__ENROUTE__GLYMPSE__
#define TRACKINGAPI_H__ENROUTE__GLYMPSE__

#include "../core/GlympseApi.h"
#include "../core/Toolbox/Listener/IListener.h"
#include "../core/Toolbox/Listener/ISource.h"

#include "api/IGlobalConfig.h"
#include "api/IPhaseConfig.h"
#include "api/IOrgConfig.h"
#include "api/IOrganization.h"
#include "api/IAgent.h"
#include "api/IOperation.h"
#include "api/ITask.h"
#include "api/ISession.h"
#include "api/IActiveAgent.h"
#include "api/IDiagnosticsCollector.h"
#include "api/IEtaPlanner.h"
#include "api/ITaskManager.h"
#include "api/IAgentManager.h"
#include "api/ISessionManager.h"
#include "api/IActiveAgentsManager.h"
#include "api/IEnRouteManager.h"
#include "api/EnRouteConstants.h"
#include "api/EnRouteEvents.h"
#include "api/EE.h"

#include "api/EnRouteFactory.h"
#include "api/ObjectEncoder.h"

#ifdef __OBJC__
#import "ios/GETListener.h"
#import "ios/GETHelpers.h"
#endif // __OBJC__

#endif // !TRACKINGAPI_H__ENROUTE__GLYMPSE__
