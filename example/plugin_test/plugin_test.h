#pragma once

#include "vasPlugin.h"

class Test;

class PluginTest : public vasPlugin
{
public:
    VAS_PLUGIN(PluginTest, "plugin.test")
    
    virtual void start() override;
    
    virtual void stop() override;
    
private:
    Test *m_pTest;
};
