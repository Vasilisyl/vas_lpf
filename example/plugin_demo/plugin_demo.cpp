#include <iostream>
#include "plugin_demo.h"
#include "demo.h"

void PluginDemo::start()
{
    std::cout << "start vas plugin plugin.demo !" << std::endl;
    
    m_pDemo = new Demo();
}

void PluginDemo::stop()
{
    std::cout << "stop vas plugin plugin.demo !" << std::endl;
    
    delete m_pDemo;
    m_pDemo = nullptr;
}

VAS_REGIST_PLUGIN_ID(PluginDemo) /*VAS_REGIST_PLUGIN_ID注册为一个插件，插件ID为"plugin.demo"*/



