//------------------------------------------------------------------------------
//
// Copyright (c) 2016 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef OBJECTENCODER_H__ENROUTE__GLYMPSE__
#define OBJECTENCODER_H__ENROUTE__GLYMPSE__

namespace Glympse
{
namespace EnRoute
{

class ObjectEncoder
{
    public: static GPrimitive valueToPrimitive(const GCommonObj& obj);
    private: static GPrimitive valueToPrimitive(bool val);
    private: static GPrimitive valueToPrimitive(int64 val);
    private: static GPrimitive valueToPrimitive(double val);
    private: static GPrimitive parseString(const GString& val);
    private: static GPrimitive parseLong(const GLong& val);
    private: static GPrimitive parsePrimitiveArray(const GArray<GPrimitive>::ptr& val);
    private: static GPrimitive parseTaskArray(const GArray<GTask>::ptr& val);
    private: static GPrimitive parseStringArray(const GArray<GString>::ptr& val);
    private: static GPrimitive parseInviteArray(const GArray<GInvite>::ptr& val);
    private: static GPrimitive parseLocationList(const GList<GLocation>::ptr& val);
    private: static GPrimitive parsePlace(const GPlace& obj);
    private: static GPrimitive parseLocation(const GLocation& obj);
    private: static GPrimitive parseAgent(const GAgent& obj);
    private: static GPrimitive parseGlobalConfig(const GGlobalConfig& obj);
    private: static GPrimitive parseInvite(const GInvite& obj);
    private: static GPrimitive parseLatLng(const GLatLng& obj);
    private: static GPrimitive parseOperation(const GOperation& obj);
    private: static GPrimitive parseOrganization(const GOrganization& obj);
    private: static GPrimitive parseOrgConfig(const GOrgConfig& obj);
    private: static GPrimitive parseSession(const GSession& obj);
    private: static GPrimitive parseTask(const GTask& obj);
    private: static GPrimitive parseTicket(const GTicket& obj);
    private: static GPrimitive parseTrack(const GTrack& obj);
};

}
}

#endif // !OBJECTENCODER_H__ENROUTE__GLYMPSE__
