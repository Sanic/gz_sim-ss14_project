#ifndef _GAZEBOTESTSERVER_H_
#define _GAZEBOTESTSERVER_H_

#include "abstractgazebotestserver.h"
#include "TestMethods.hh"

class GazeboTestServer : public AbstractGazeboTestServer
{
    public:
        GazeboTestServer();
        void registerTestMethodImpl(TestMethods* _testMethodsImpl);
        virtual bool onObject(const std::string& object, const std::string& surface);
    private:
        TestMethods* testMethodsImpl;
};

#endif
