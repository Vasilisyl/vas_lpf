#include <iostream>
#include "plugin_demo.h"
#include "demo.h"

void PluginDemo::start()
{
    std::cout << "start vas plugin plugin.demo !" << std::endl;
    
    m_pDemo = new Demo(20);
}

void PluginDemo::stop()
{
    std::cout << "stop vas plugin plugin.demo !" << std::endl;
    
    delete m_pDemo;
    m_pDemo = nullptr;
}

VAS_REGIST_PLUGIN_ID(PluginDemo, "plugin.demo")



