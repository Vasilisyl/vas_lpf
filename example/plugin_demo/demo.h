#pragma once

#include "vasPluginContext.h"

class Demo
{
public:
    Demo(int demoInt);
    ~Demo();
    
    void demoFunc();

    /*demo's event*/
    void demoEvent(VAS::vasProperty property);
    
private:
    int m_demoInt;
};
