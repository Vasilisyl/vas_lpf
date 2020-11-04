#pragma once

#include <string>
#include <map>
#include "vasDefined.h"

/*获取框架上下文实例*/
#define VAS_PLUGIN_CONTEXT \
    VAS::vasPluginContext::getInstance()

namespace VAS {

class vasEventHandler;

/**
 * @brief vasPluginContext 框架上下文类
 */
VAS_USER_INTERFACE_CLASS vasPluginContext final
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
     * @brief  publishEvent 发布事件，当事件发布时，对应使用相同的groupKey/actionKey订阅的事件将被调用，并获得事件发布时的入参property
     * @param  groupKey     事件“组”键值，一个groupKey可对应一个或多个actionKey
     * @param  actionKey    事件“组”内“动作”键值，一个组中的actionKey唯一对应一个事件vasEvent
     * @param  property     发布事件时需要传递的参数列表，vasProperty中可填充多个参数对象，以不同的参数键值区分
     */
    void publishEvent(const std::string &groupKey, const std::string &actionKey, VAS::vasProperty property);

    /**
     * @brief  subscribeEvent 订阅事件，当任何地方使用相同的groupKey/actionKey发布事件时，该订阅事件将被调用，并获得事件发布时的入参variant
     * @note                 （注意：subscribeEvent应该与unSubscribeEvent一一对应，如同new和delete的关系，
     *                              subscribeEvent的调用者应当在不需要订阅事件时或析构释放时调用unSubscribeEvent取消事件的订阅）
     * @param  groupKey       事件“组”键值，一个groupKey可对应一个或多个actionKey
     * @param  actionKey      事件“组”内“动作”键值，一个组中的actionKey唯一对应一个事件vasEven
     * @param  event          注册的事件，事件触发时，获取到对应publishEvent传入的参数列表vasProperty
     */
    void subscribeEvent(const std::string &groupKey, const std::string &actionKey, VAS::vasEvent event);

    /**
     * @brief  unSubscribeEvent 取消订阅，取消指定的groupKey/actionKey对应事件的订阅
     * @note                   （注意：subscribeEvent应该与unSubscribeEvent一一对应，如同new和delete的关系，
     *                                subscribeEvent的调用者应当在不需要订阅事件时或析构释放时调用unSubscribeEvent取消事件的订阅）
     * @param  actionKey        事件“组”内“动作”键值，一个组中的actionKey唯一对应一个事件vasEven
     */
    void unSubscribeEvent(const std::string &groupKey, const std::string &actionKey);
    
private:
    vasEventHandler                              *m_pEventHandler;
    std::map<std::string, VAS::vasPluginInfo_St>  m_pluginsMap;
};

} /*namespace VAS*/