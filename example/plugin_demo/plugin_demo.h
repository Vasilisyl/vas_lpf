#pragma once

#include "vasPlugin.h"

class Demo;

class PluginDemo : public VAS::vasPlugin
{
public:
    VAS_PLUGIN(PluginDemo, "plugin.demo") /*VAS_PLUGIN声明为一个插件，插件ID为"plugin.demo"*/
    
    virtual void start() override;
    
    virtual void stop() override;
    
private:
    Demo *m_pDemo;
};
