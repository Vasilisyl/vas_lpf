#pragma once

#include "vasPlugin.h"

class Test;

class PluginTest : public VAS::vasPlugin
{
public:
    VAS_PLUGIN(PluginTest, "plugin.test") /*VAS_PLUGIN声明为一个插件，插件ID为"plugin.test"*/
    
    virtual void start() override;
    
    virtual void stop() override;
    
private:
    Test *m_pTest;
};
