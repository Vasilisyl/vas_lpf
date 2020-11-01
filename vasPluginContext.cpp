#include <mutex>
#include "vasPluginContext.h"
#include "vasPlugin.h"

#ifdef __cplusplus
extern "C" {
#endif
#include <dlfcn.h>
#ifdef __cplusplus
}
#endif

typedef VAS::vasPlugin *(*P_CREATE_PLUGIN_FUNC)();

VAS::vasPluginContext::vasPluginContext()
{
    
}

VAS::vasPluginContext::~vasPluginContext()
{
    
}

VAS::vasPluginContext *VAS::vasPluginContext::getInstance()
{
    static vasPluginContext *s_pInstance = nullptr;
    static std::mutex s_mutex;
    std::unique_lock<std::mutex> lock(s_mutex);
    if (!s_pInstance) {
        s_pInstance = new vasPluginContext();
    }
    return s_pInstance;
}

std::string VAS::vasPluginContext::install(const std::string& pluginPath, std::string *pErrStr)
{
    VAS_EMPTY_STR_SET(pErrStr);
    std::string pgId;
    do {
        if (pluginPath.empty()) { 
            VAS_ERROR_SET(pErrStr, "plugin's path is empty !");
            break;
        }
        
        void *pHandle = dlopen(pluginPath.c_str(), RTLD_LAZY);
        if (!pHandle) {
            VAS_ERROR_SET(pErrStr, dlerror());
            break;
        }
        
        P_CREATE_PLUGIN_FUNC pCreate = (P_CREATE_PLUGIN_FUNC)dlsym(pHandle, "createPlugin");
        if (!pCreate) {
            VAS_ERROR_SET(pErrStr, dlerror());
            break;
        }
        
        VAS::vasPlugin *pPlugin = pCreate();
        if (!pPlugin) {
            VAS_ERROR_SET(pErrStr, "get plugin info failed !");
            break;
        }
        
        pgId = pPlugin->getPluginId();
        
        VAS::vasPluginInfo_St pluginInfo;
        pluginInfo._pHandle = pHandle;
        pluginInfo._pluginPath = pluginPath;
        pluginInfo._pPlugin = pPlugin;
        pluginInfo._state = VAS::VAS_PS_INSTALLED;
        
        m_pluginsMap[pgId] = pluginInfo;
        
        VAS_INFO_SET(pErrStr, "no error !");
        
    } while (0);
    return pgId;
}

bool VAS::vasPluginContext::uninstall(const std::string &pluginId, std::string *pErrStr)
{
    VAS_EMPTY_STR_SET(pErrStr);
    bool rslt = false;
    do {
        
        if (pluginId.empty() || m_pluginsMap.find(pluginId) == m_pluginsMap.end()) {
            VAS_ERROR_SET(pErrStr, "don't find the plugin id !");
            break;
        }
        
        VAS::vasPluginInfo_St &pluginInfo = m_pluginsMap.find(pluginId)->second;
        if (!pluginInfo._pPlugin || !pluginInfo._pHandle) {
            VAS_ERROR_SET(pErrStr, "an error occurred with Uninstall !");
            break;
        }
        
        if (pluginInfo._state == VAS::VAS_PS_STARTING) {
            pluginInfo._pPlugin->stop();
        }
        
        delete pluginInfo._pPlugin;
        pluginInfo._pPlugin = nullptr;
        
        dlclose(pluginInfo._pHandle);
        pluginInfo._pHandle = nullptr;
        pluginInfo._pluginPath.clear();
        pluginInfo._state = VAS::VAS_PS_UNINSTALLED;

        rslt = true;
        
    } while (0);
    return rslt;
}

bool VAS::vasPluginContext::startPlugin(const std::string &pluginId, std::string *pErrStr)
{
    VAS_EMPTY_STR_SET(pErrStr);
    bool rslt = false;
    do {
        if (m_pluginsMap.find(pluginId) == m_pluginsMap.end()) {
            VAS_ERROR_SET(pErrStr, "plugin is not exists !");
            break;
        }
        VAS::vasPluginInfo_St &pluginInfo = m_pluginsMap.find(pluginId)->second;
        
        switch (pluginInfo._state) {
            case VAS::VAS_PS_INSTALLED:
            case VAS::VAS_PS_STOPPING:
                pluginInfo._pPlugin->start();
                pluginInfo._state = VAS::VAS_PS_STARTING;
                rslt = true;
                break;
            case VAS::VAS_PS_UNINSTALLED:
                VAS_ERROR_SET(pErrStr, "start plugin failed ! the plugin is uninstalled !");
                break;
            case VAS::VAS_PS_STARTING:
                VAS_ERROR_SET(pErrStr, "start plugin failed ! the plugin has been started !");
                break;
            default:
                break;
        }
        
    } while (0);
    return rslt;
}

bool VAS::vasPluginContext::stopPlugin(const std::string& pluginId, std::string *pErrStr)
{
    VAS_EMPTY_STR_SET(pErrStr);
    bool rslt = false;
    do {
        if (m_pluginsMap.find(pluginId) == m_pluginsMap.end()) {
            VAS_ERROR_SET(pErrStr, "plugin is not exists !");
            break;
        }
        VAS::vasPluginInfo_St &pluginInfo = m_pluginsMap.find(pluginId)->second;
        
        switch (pluginInfo._state) {
            case VAS::VAS_PS_STARTING:
                pluginInfo._pPlugin->stop();
                pluginInfo._state = VAS::VAS_PS_STOPPING;
                rslt = true;
                break;
            case VAS::VAS_PS_INSTALLED:
                VAS_ERROR_SET(pErrStr, "stop plugin failed ! the plugin is not started !");
                break;
            case VAS::VAS_PS_STOPPING:
                VAS_ERROR_SET(pErrStr, "stop plugin failed ! the plugin has been stopped !");
                break;
            case VAS::VAS_PS_UNINSTALLED:
                VAS_ERROR_SET(pErrStr, "stop plugin failed ! the plugin is uninstalled !");
                break;
            default:
                break;
        }
    } while (0);
    return rslt;
}

