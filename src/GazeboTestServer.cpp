#include "GazeboTestServer.hh"

using namespace jsonrpc;
using namespace std;

GazeboTestServer::GazeboTestServer() : AbstractGazeboTestServer(new HttpServer(8080))
{
	this->testMethodsImpl = NULL;
}

void GazeboTestServer::registerTestMethodImpl(TestMethods* _testMethodsImpl)
{
	this->testMethodsImpl = _testMethodsImpl;
}

bool GazeboTestServer::onObject(const std::string& object, const std::string& surface)
{
    //return this->_onEntity(object, surface);
    return true;
}
