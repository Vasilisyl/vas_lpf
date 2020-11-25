#include "vasServiceHandler.h"
#include "vasService.h"

VAS::vasServiceHandler::vasServiceHandler()
{

}

VAS::vasServiceHandler::~vasServiceHandler()
{

}

bool VAS::vasServiceHandler::registService(VAS::vasService *pSvc) noexcept
{
    if (!pSvc) { return false; }
    m_svcMap.insert(std::pair<std::string, VAS::vasService *>(pSvc->getServiceId(), pSvc));
    return true;
}

bool VAS::vasServiceHandler::unregistService(VAS::vasService *pSvc) noexcept
{
    if (!pSvc) { return false; }
    std::map<std::string, VAS::vasService *>::iterator svcIt = m_svcMap.find(pSvc->getServiceId());
    if (svcIt == m_svcMap.end()) {
        return false;
    }
    m_svcMap.erase(svcIt);
    return true;
}

template<>
VAS::vasService *VAS::vasServiceHandler::getService<VAS::vasService *>(const std::string &svcId) noexcept
{
    VAS::vasService * pSvc = nullptr;
    do {
        std::map<std::string, VAS::vasService *>::iterator svcIt = m_svcMap.find(svcId);
        if (svcIt == m_svcMap.end()) {
            break;
        }
        pSvc = svcIt->second;
    } while (0);
    return pSvc;
}