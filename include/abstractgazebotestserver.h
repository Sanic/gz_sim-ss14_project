/**
 * THIS FILE IS GENERATED BY jsonrpcstub, DO NOT CHANGE IT!!!!!
 */

#ifndef _ABSTRACTGAZEBOTESTSERVER_H_
#define _ABSTRACTGAZEBOTESTSERVER_H_

#include <jsonrpc/rpc.h>

class AbstractGazeboTestServer : public jsonrpc::AbstractServer<AbstractGazeboTestServer>
{
    public:
        AbstractGazeboTestServer(jsonrpc::AbstractServerConnector* conn) :
            jsonrpc::AbstractServer<AbstractGazeboTestServer>(conn) 
        {
            this->bindAndAddMethod(new jsonrpc::Procedure("onObject", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_BOOLEAN, "object",jsonrpc::JSON_STRING,"surface",jsonrpc::JSON_STRING, NULL), &AbstractGazeboTestServer::onObjectI);

        }
        
        inline virtual void onObjectI(const Json::Value& request, Json::Value& response) 
        {
            response = this->onObject(request["object"].asString(), request["surface"].asString());
        }


        virtual bool onObject(const std::string& object, const std::string& surface) = 0;

};
#endif //_ABSTRACTGAZEBOTESTSERVER_H_
