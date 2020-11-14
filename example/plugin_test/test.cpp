#include "test.h"
#include <iostream>
#include <vasDefined.h>
#include <vasVariant.h>
#include <vasPluginContext.h>
#include "../example_common/PrintService.h"

Test::Test()
{
    
}

Test::~Test()
{
    
}

void Test::toDo()
{
    /*触发事件，在plugin.test插件中完成与plugin.demo插件之间的交互*/
    doTriggered();

    /*调用服务*/
    doService();
}

void Test::doTriggered()
{
    /*触发事件*/
    VAS::vasVariant var;
    VAS::vasProperty property;
    
    var.set<std::string>("vas_lpf");
    property["name"] = var;

    var.set<unsigned int>(25);
    property["age"] = var;

    var.set<double>(3.1415);
    property["money"] = var;

    /*指定触发事件group/event1*/
    VAS_PLUGIN_CONTEXT->triggerEvent("group", "event1", property);

    /*指定触发事件group/event2*/
    VAS_PLUGIN_CONTEXT->triggerEvent("group", "event2", property);

    /*触发组"group"中的所有事件*/
    VAS_PLUGIN_CONTEXT->triggerEvent("group", property);
}

void Test::doService()
{
    /*获取服务PrintService*/
    PrintService *pSrc = VAS_PLUGIN_CONTEXT->getService<PrintService *>("service.print");
    if (pSrc) {
        /*调用PrintService服务提供的接口print*/
        pSrc->print("*********** call PrintService::print(const std::string &) ***********");
    }
    else {
        std::cout << "get service failed !" << std::endl;
    }
}
