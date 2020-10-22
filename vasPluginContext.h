#pragma once

#include <string>
#include <map>
#include "vasDefined.h"

#define VAS_PLUGIN_CONTEXT \
    vasPluginContext::getInstance()

class vasPluginContext final
{
    vasPluginContext();
public:
    ~vasPluginContext();
    
    static vasPluginContext *getInstance();
    
    std::string install(const std::string &pluginPath, std::string *pErrStr = nullptr);
    bool uninstall(const std::string &pluginId, std::string *pErrStr = nullptr);
    
    bool startPlugin(const std::string &pluginId, std::string *pErrStr = nullptr);
    bool stopPlugin(const std::string &pluginId, std::string *pErrStr = nullptr);
    
private:
    std::map<std::string, VAS::vasPluginInfo_St> m_pluginsMap;
};


