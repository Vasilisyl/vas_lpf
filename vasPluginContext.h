#pragma once

#include <string>
#include <map>
#include "vasDefined.h"

/*获取框架上下文实例*/
#ifndef VAS_PLUGIN_CONTEXT
    #define VAS_PLUGIN_CONTEXT \
        VAS::vasPluginContext::getInstance()
#endif /*VAS_PLUGIN_CONTEXT*/

namespace VAS {

class vasEventHandler;
class vasEvent;

/**
 * @brief vasPluginContext 框架上下文类
 */
VAS_USER_INTERFACE_CLASS vasPluginContext VAS_DISABLED_INHERIT
{
    VAS_DISABLED_COPY(vasPluginContext)
    vasPluginContext();
public:
    ~vasPluginContext();
    
    static vasPluginContext *getInstance();

    /* * * * * * * 1.插件接口 * * * * * * */
    
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

    /* * * * * * * 2.事件接口 * * * * * * */

    /**
     * @brief  triggerEvent  触发事件，当事件触发时，对应事件组中的所有注册的事件将会被调用，并获得参数列表property
     * @param  eventGroupKey 事件组唯一键值，一个事件组中包含一个或多个事件
     * @param  property      触发事件时需要传递的参数列表，vasProperty中可填充多个参数对象，以不同的参数键值区分
     */
    void triggerEvent(const std::string &eventGroupKey, VAS::vasProperty property);

    /**
     * @brief  triggerEvent  触发事件，当事件触发时，对应事件组中的所有注册的事件将会被调用，并获得参数列表property
     * @param  eventGroupKey 事件组唯一键值，一个事件组中包含一个或多个事件
     * @param  eventKey      事件键值，在同一个事件组中，一个事件键值与一个事件一一对应
     * @param  property      触发事件时需要传递的参数列表，vasProperty中可填充多个参数对象，以不同的参数键值区分
     */
    void triggerEvent(const std::string &eventGroupKey, const std::string &eventKey, VAS::vasProperty property);

    /**
     * @brief  registEvent    注册事件，当任何地方触发事件时，该事件组中的所有注册的事件将会被调用，并获得参数列表property
     * @note                  （注意：registEvent应该与unregistEvent一一对应，如同new和delete的关系，
     *                               registEvent的调用者应当在不需要响应事件的触发时或事件所属对象析构释放时调用unregistEvent取消事件的注册）
     * @param  eventGroupKey  事件组唯一键值，一个事件组中包含一个或多个事件
     * @param  eventKey       事件键值，在同一个事件组中，一个事件键值与一个事件一一对应
     * @param  event          事件
     */
    void registEvent(const std::string &eventGroupKey, const std::string &eventKey, VAS::vasEvent event);

    /**
     * @brief  unregistEvent  取消事件的注册，取消指定事件的注册
     * @note                  （注意：registEvent应该与unregistEvent一一对应，如同new和delete的关系，
     *                               registEvent的调用者应当在不需要响应事件的触发时或事件所属对象析构释放时调用unregistEvent取消事件的注册）
     * @param  eventGroupKey  事件组唯一键值，一个事件组中包含一个或多个事件
     * @param  eventKey       事件键值，在同一个事件组中，一个事件键值与一个事件一一对应
     */
    void unregistEvent(const std::string &eventGroupKey, const std::string &eventKey);
    
private:
    vasEventHandler                              *m_pEventHandler;
    std::map<std::string, VAS::vasPluginInfo_St>  m_pluginsMap;
};

} /*namespace VAS*/