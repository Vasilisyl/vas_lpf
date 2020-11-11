#pragma once

#include <map>
#include "vasDefined.h"

namespace VAS {

class vasPluginContext;
class vasService;

/**
 * @brief vasServiceHandler 服务管理器类
 */
VAS_PRIVATE_IMPL_CLASS vasServiceHandler VAS_DISABLED_INHERIT
{
    VAS_DISABLED_COPY(vasServiceHandler)
    VAS_DECLARE_FRIEND_CONTEXT

    vasServiceHandler();
    ~vasServiceHandler();

    /**
     * @brief  registService   注册服务
     * @param  pSvc            服务基类指针
     * @return bool            注册结果
     */
    bool registService(VAS::vasService *pSvc);

    /**
     * @brief  unregistService 取消服务的注册
     * @param  pSvc            服务基类指针
     * @return bool            注册结果
     */
    bool unregistService(VAS::vasService *pSvc);

    /**
     * @brief  getService      获取服务
     * @param  pSvcId          注册服务的ID
     * @return SERVICE_T       服务类或服务派生类类指针，获取失败返回nullptr
     */
    template<typename SERVICE_T>
    SERVICE_T getService(const std::string &svcId);

private:
    std::map<std::string, VAS::vasService *> m_svcMap;
};

template<>
VAS::vasService *VAS::vasServiceHandler::getService<VAS::vasService *>(const std::string &svcId);

template<typename SERVICE_T>
SERVICE_T VAS::vasServiceHandler::getService(const std::string &svcId)
{
    SERVICE_T pSvc = nullptr;
    do {
        std::map<std::string, VAS::vasService *>::iterator svcIt = m_svcMap.find(svcId);
        if (svcIt == m_svcMap.end()) {
            break;
        }
        pSvc = dynamic_cast<SERVICE_T>(svcIt->second);
    } while (0);
    return pSvc;
}

} /*namespace VAS*/