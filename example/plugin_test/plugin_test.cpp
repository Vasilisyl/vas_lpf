#include <iostream>
#include "plugin_test.h"
#include "test.h"

void PluginTest::start()
{
    std::cout << "start vas plugin plugin.test !" << std::endl;
    
    m_pTest = new Test();
    m_pTest->toDo();
}

void PluginTest::stop()
{
    std::cout << "stop vas plugin plugin.test !" << std::endl;
    
    delete m_pTest;
    m_pTest = nullptr;
}

VAS_REGIST_PLUGIN_ID(PluginTest) /*VAS_REGIST_PLUGIN_ID注册为一个插件，插件ID为"plugin.test"*/



