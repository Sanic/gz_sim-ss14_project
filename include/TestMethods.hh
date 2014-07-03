#ifndef _TESTMETHODS_H_
#define _TESTMETHODS_H_


class TestMethods
{
    public:
        virtual bool OnObject(const std::string& object, const std::string& surface);
        virtual ~TestMethods();
};

#endif
