#pragma once

#include "vasPluginContext.h"

class Demo
{
public:
    Demo();
    ~Demo();

    /*demo's event*/
    void demoEvent(VAS::vasProperty property);
};
