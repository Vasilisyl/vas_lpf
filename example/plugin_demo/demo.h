#pragma once

#include "vasPluginContext.h"
#include "../example_common/PrintService.h"

/*Demo继承自定义的服务类PrintService*/
class Demo : public PrintService
{
public:
    Demo();
    ~Demo();

    /*demo's event*/
    void demoEvent1(VAS::vasProperty property);

    void demoEvent2(VAS::vasProperty property);

    /*Demo实现服务的接口*/
    virtual void print(const std::string &str) override;
};
