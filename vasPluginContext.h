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
     * @brief  publishEvent  发布事件，当事件发布时，对应事件组中的所有事件将会触发，并获得事件发布时的入参property
     * @param  eventGroupKey 事件组唯一键值，一个事件组中包含一个或多个事件
     * @param  property      发布事件时需要传递的参数列表，vasProperty中可填充多个参数对象，以不同的参数键值区分
     */
    void publishEvent(const std::string &eventGroupKey, VAS::vasProperty property);

    /**
     * @brief  publishEvent  发布事件，当事件发布时，对应事件组中的所有事件将会触发，并获得事件发布时的入参property
     * @param  eventGroupKey 事件组唯一键值，一个事件组中包含一个或多个事件
     * @param  eventKey      事件键值，在同一个事件组中，一个事件键值与一个事件一一对应
     * @param  property      发布事件时需要传递的参数列表，vasProperty中可填充多个参数对象，以不同的参数键值区分
     */
    void publishEvent(const std::string &eventGroupKey, const std::string &eventKey, VAS::vasProperty property);

    /**
     * @brief  subscribeEvent 订阅事件，当任何地方发布事件时，该事件组中的所有事件将会触发，并获得事件发布时的入参property
     * @note                  （注意：subscribeEvent应该与unSubscribeEvent一一对应，如同new和delete的关系，
     *                               subscribeEvent的调用者应当在不需要订阅事件时或析构释放时调用unSubscribeEvent取消事件的订阅）
     * @param  eventGroupKey  事件组唯一键值，一个事件组中包含一个或多个事件
     * @param  eventKey       事件键值，在同一个事件组中，一个事件键值与一个事件一一对应
     * @param  event          事件
     */
    void subscribeEvent(const std::string &eventGroupKey, const std::string &eventKey, VAS::vasEvent event);

    /**
     * @brief  unSubscribeEvent 取消订阅，取消指定的eventKey对应事件的订阅
     * @note                    （注意：subscribeEvent应该与unSubscribeEvent一一对应，如同new和delete的关系，
     *                                subscribeEvent的调用者应当在不需要订阅事件时或析构释放时调用unSubscribeEvent取消事件的订阅）
     * @param  eventGroupKey    事件组唯一键值，一个事件组中包含一个或多个事件
     * @param  eventKey         事件键值，在同一个事件组中，一个事件键值与一个事件一一对应
     */
    void unSubscribeEvent(const std::string &eventGroupKey, const std::string &eventKey);
    
private:
    vasEventHandler                              *m_pEventHandler;
    std::map<std::string, VAS::vasPluginInfo_St>  m_pluginsMap;
};

} /*namespace VAS*/