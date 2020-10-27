#pragma once

#include <string>
#include <map>
#include "vasDefined.h"

/*获取框架上下文实例*/
#define VAS_PLUGIN_CONTEXT \
    vasPluginContext::getInstance()
    
/**
 * @brief 框架上下文类
 */
class vasPluginContext final
{
    vasPluginContext();
public:
    ~vasPluginContext();
    
    static vasPluginContext *getInstance();
    
    /**
     * @brief  install     安装插件
     * @param  pluginPath  插件路径
     * @param  pErrStr     错误码
     * @return std::string 插件ID
     */
    std::string install(const std::string &pluginPath, std::string *pErrStr = nullptr);

    /**
     * @brief  uninstall   卸载插件
     * @param  pluginId    插件ID
     * @param  pErrStr     错误码
     * @return bool        卸载结果
     */
    bool uninstall(const std::string &pluginId, std::string *pErrStr = nullptr);
    
    /**
     * @brief  startPlugin 启动插件
     * @param  pluginId    插件ID
     * @param  pErrStr     错误码
     * @return bool        启动结果
     */
    bool startPlugin(const std::string &pluginId, std::string *pErrStr = nullptr);

    /**
     * @brief  stopPlugin  停止插件
     * @param  pluginId    插件ID
     * @param  pErrStr     错误码
     * @return bool        停止结果
     */
    bool stopPlugin(const std::string &pluginId, std::string *pErrStr = nullptr);
    
private:
    std::map<std::string, VAS::vasPluginInfo_St> m_pluginsMap;
};


