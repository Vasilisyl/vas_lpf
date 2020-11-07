#include "demo.h"
#include <iostream>
#include <functional>
#include "vasVariant.h"
#include "vasEvent.h"

Demo::Demo(int demoInt)
    : m_demoInt(demoInt)
{
    std::cout << "constract Demo() !" << std::endl;

    /*注册事件*/
    VAS_PLUGIN_CONTEXT->registEvent("group", "event", VAS_EVENT_M(&Demo::demoEvent, this));
}

Demo::~Demo()
{
    std::cout << "release Demo() !" << std::endl;
}

void Demo::demoFunc()
{
    std::cout << "The Demo::m_demoInt = " << m_demoInt << " !" << std::endl;
}

void Demo::demoEvent(VAS::vasProperty property)
{
    std::cout << "The demo's event is triggered !" << std::endl;

    /*从property中根据参数键值取出数据*/
    VAS::vasVariant var;
    var = property["name"];
    std::cout << "the name = " << var.get<std::string>() << std::endl;

    var = property["age"];
    std::cout << "the age = " << var.get<unsigned int>() << std::endl;

    var = property["money"];
    std::cout << "the money = " << var.get<double>() << std::endl;
}
