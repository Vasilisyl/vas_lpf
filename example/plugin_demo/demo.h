#pragma once

#include "vasPluginContext.h"

class Demo
{
public:
    Demo();
    ~Demo();

    /*demo's event*/
    void demoEvent1(VAS::vasProperty property);

    void demoEvent2(VAS::vasProperty property);
};
