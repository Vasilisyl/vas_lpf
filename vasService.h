#pragma once

#include "vasDefined.h"

namespace VAS {

/**
 * @brief vasService 服务接口类
 */
VAS_USER_INTERFACE_CLASS vasService
{
    VAS_DISABLED_COPY(vasService)
public:
    vasService(const std::string svcId)
        : m_svcId(svcId) {}
    virtual ~vasService() {}

    /**
     * @brief  getServiceId 获取服务ID
     * @return std::string  服务ID
     */
    const std::string &getServiceId() const { return m_svcId; }

private:
    const std::string m_svcId;
};

} /*namespace VAS*/