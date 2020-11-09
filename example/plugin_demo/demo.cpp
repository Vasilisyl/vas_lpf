#include "demo.h"
#include <iostream>
#include <functional>
#include <vasVariant.h>
#include <vasEvent.h>

Demo::Demo()
{
    /*注册事件*/
    VAS_PLUGIN_CONTEXT->registEvent("group", "event", VAS_EVENT_M(&Demo::demoEvent, this));
}

Demo::~Demo()
{
    /*取消事件注册*/
    VAS_PLUGIN_CONTEXT->unregistEvent("group", "event");
}

void Demo::demoEvent(VAS::vasProperty property)
{
    std::cout << "* * * * * * * * * *" << std::endl;

    std::cout << "The demo's event is triggered !" << std::endl;

    /*从property中根据参数键值取出数据*/
    VAS::vasVariant var;
    var = property["name"];
    std::cout << "the name = " << var.get<std::string>() << std::endl;

    var = property["age"];
    std::cout << "the age = " << var.get<unsigned int>() << std::endl;

    var = property["money"];
    std::cout << "the money = " << var.get<double>() << std::endl;
    
    std::cout << "* * * * * * * * * *" << std::endl;
}
