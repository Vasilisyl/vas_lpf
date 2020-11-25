#include <mutex>
#include "vasPluginContext.h"
#include "vasPlugin.h"
#include "vasEventHandler.h"
#include "vasEvent.h"

#ifdef __cplusplus
extern "C" {
#endif
#include <dlfcn.h>
#ifdef __cplusplus
}
#endif

typedef VAS::vasPlugin *(*P_CREATE_PLUGIN_FUNC)();

VAS::vasPluginContext::vasPluginContext() noexcept
    : m_pEventHandler(new VAS::vasEventHandler()),
      m_pServiceHandler(new VAS::vasServiceHandler())
{
    
}

VAS::vasPluginContext::~vasPluginContext() noexcept
{
    delete m_pEventHandler;
    m_pEventHandler = nullptr;
}

VAS::vasPluginContext *VAS::vasPluginContext::getInstance() noexcept
{
    static vasPluginContext *s_pInstance = nullptr;
    static std::mutex s_mutex;
    std::unique_lock<std::mutex> lock(s_mutex);
    if (!s_pInstance) {
        s_pInstance = new vasPluginContext();
    }
    return s_pInstance;
}

std::string VAS::vasPluginContext::install(const std::string& pluginPath) throw(VAS::vasException)
{
    std::string pgId;
    do {
        if (pluginPath.empty()) { 
            VAS_EXCEPTION_THROW(VAS::vasPluginContext, "The plugin's path is empty !");
            break;
        }
        void *pHandle = dlopen(pluginPath.c_str(), RTLD_LAZY);
        if (!pHandle) {
            const char *pDlErr = dlerror();
            VAS_EXCEPTION_THROW(VAS::vasPluginContext, pDlErr);
            break;
        }
        
        P_CREATE_PLUGIN_FUNC pCreate = (P_CREATE_PLUGIN_FUNC)dlsym(pHandle, "createPlugin");
        if (!pCreate) {
            const char *pDlErr = dlerror();
            VAS_EXCEPTION_THROW(VAS::vasPluginContext, pDlErr);
            break;
        }
        
        VAS::vasPlugin *pPlugin = pCreate();
        if (!pPlugin) {
            VAS_EXCEPTION_THROW(VAS::vasPluginContext, \
                "Get plugin's creator failed ! Please Use \'VAS_REGIST_PLUGIN_ID\' to regist it!");
            break;
        }
        
        pgId = pPlugin->getPluginId();
        
        VAS::vasPluginInfo_St pluginInfo;
        pluginInfo._pHandle = pHandle;
        pluginInfo._pluginPath = pluginPath;
        pluginInfo._pPlugin = pPlugin;
        pluginInfo._state = VAS::VAS_PS_INSTALLED;
        
        m_pluginsMap[pgId] = pluginInfo;
        
    } while (0);
    return pgId;
}

void VAS::vasPluginContext::uninstall(const std::string &pluginId) throw(VAS::vasException)
{
    if (pluginId.empty() || m_pluginsMap.find(pluginId) == m_pluginsMap.end()) {
        VAS_EXCEPTION_THROW(VAS::vasPluginContext, \
            std::string("Cannot find the plugin ID ! The plugin ID is ") + pluginId + " !");
    }
    
    VAS::vasPluginInfo_St &pluginInfo = m_pluginsMap.find(pluginId)->second;
    if (!pluginInfo._pPlugin || !pluginInfo._pHandle) {
        VAS_EXCEPTION_THROW(VAS::vasPluginContext, \
            "An error occurred with Uninstall ! The plugin has been uninstalled or not installed correctly !");
    }
    
    if (pluginInfo._state == VAS::VAS_PS_RUNNING) {
        pluginInfo._pPlugin->stop();
    }
    
    delete pluginInfo._pPlugin;
    pluginInfo._pPlugin = nullptr;
    
    dlclose(pluginInfo._pHandle);
    pluginInfo._pHandle = nullptr;
    pluginInfo._pluginPath.clear();
    pluginInfo._state = VAS::VAS_PS_UNINSTALLED;
    return;
}

void VAS::vasPluginContext::startPlugin(const std::string &pluginId) throw(VAS::vasException)
{
    if (m_pluginsMap.find(pluginId) == m_pluginsMap.end()) {
        VAS_EXCEPTION_THROW(VAS::vasPluginContext, \
            std::string("The plugin is not exists ! The plugin ID is ") + pluginId + " !");
    }
    VAS::vasPluginInfo_St &pluginInfo = m_pluginsMap.find(pluginId)->second;
    
    switch (pluginInfo._state) {
        case VAS::VAS_PS_INSTALLED:
            pluginInfo._pPlugin->start();
            pluginInfo._state = VAS::VAS_PS_RUNNING;
            break;
        case VAS::VAS_PS_UNINSTALLED:
            VAS_EXCEPTION_THROW(VAS::vasPluginContext, \
                std::string("Start plugin failed ! The plugin is uninstalled ! The plugin ID is ") + pluginId + " !");
            break;
        case VAS::VAS_PS_RUNNING:
            VAS_EXCEPTION_THROW(VAS::vasPluginContext, \
                std::string("Start plugin failed ! The plugin has been started ! The plugin ID is ") + pluginId + " !");
            break;
        default:
            break;
    }
    return;
}

void VAS::vasPluginContext::stopPlugin(const std::string& pluginId) throw(VAS::vasException)
{
    if (m_pluginsMap.find(pluginId) == m_pluginsMap.end()) {
        VAS_EXCEPTION_THROW(VAS::vasPluginContext, \
            std::string("The plugin is not exists ! The plugin ID is ") + pluginId + " !");
    }
    VAS::vasPluginInfo_St &pluginInfo = m_pluginsMap.find(pluginId)->second;
    
    switch (pluginInfo._state) {
        case VAS::VAS_PS_RUNNING:
            pluginInfo._pPlugin->stop();
            pluginInfo._state = VAS::VAS_PS_INSTALLED;
            break;
        case VAS::VAS_PS_INSTALLED:
            VAS_EXCEPTION_THROW(VAS::vasPluginContext, \
                std::string("Stop plugin failed ! The plugin is not started ! The plugin ID is ") + pluginId + " !");
            break;
        case VAS::VAS_PS_UNINSTALLED:
            VAS_EXCEPTION_THROW(VAS::vasPluginContext, \
                std::string("Stop plugin failed ! The plugin is uninstalled ! The plugin ID is ") + pluginId + " !");
            break;
        default:
            break;
    }
    return;
}

void VAS::vasPluginContext::triggerEvent(const std::string &eventGroupKey, VAS::vasProperty property) noexcept
{
    m_pEventHandler->triggerEvent(eventGroupKey, property);
}

void VAS::vasPluginContext::triggerEvent(const std::string &eventGroupKey, const std::string &eventKey, VAS::vasProperty property) noexcept
{
    m_pEventHandler->triggerEvent(eventGroupKey, eventKey, property);
}

void VAS::vasPluginContext::registEvent(const std::string &eventGroupKey, const std::string &eventKey, VAS::vasEvent event) noexcept
{
    m_pEventHandler->registEvent(eventGroupKey, eventKey, event);
}

void VAS::vasPluginContext::unregistEvent(const std::string &eventGroupKey, const std::string &eventKey) noexcept
{
    m_pEventHandler->unregistEvent(eventGroupKey, eventKey);
}

bool VAS::vasPluginContext::registService(VAS::vasService *pSvc) noexcept
{
    return m_pServiceHandler->registService(pSvc);
}

bool VAS::vasPluginContext::unregistService(VAS::vasService *pSvc) noexcept
{
    return m_pServiceHandler->unregistService(pSvc);
}