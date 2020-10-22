#pragma once

#include <string>
#include <map>
#include "vasDefined.h"

class vasPluginContext final
{
    vasPluginContext();
public:
    ~vasPluginContext();
    
    static vasPluginContext *getInstance();
    
    std::string install(const std::string &pluginPath, std::string *pErrStr = nullptr);
    bool unInstall(const std::string &pluginId, std::string *pErrStr = nullptr);
    
    void startPlugin(const std::string &pluginId);
    void stopPlugin(const std::string &pluginId);
    
private:
    std::map<std::string, VAS::vasPluginInfo_St> m_pluginsMap;
};


