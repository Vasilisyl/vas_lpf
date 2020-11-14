#pragma once

#include "vasService.h"

/*声明服务接口类*/
VAS_SERVICE_INTERFACE_CLASS PrintService : public VAS::vasService
{
public:
    VAS_SERVICE(PrintService, "service.print")

    virtual ~PrintService() {}

    /*声明PrintService服务的接口print*/
    virtual void print(const std::string &str) = 0;
};