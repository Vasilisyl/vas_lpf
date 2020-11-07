#pragma once

#include "vasPlugin.h"

class Demo;

class PluginDemo : public VAS::vasPlugin
{
public:
    VAS_PLUGIN(PluginDemo, "plugin.demo")
    
    virtual void start() override;
    
    virtual void stop() override;
    
private:
    Demo *m_pDemo;
};
