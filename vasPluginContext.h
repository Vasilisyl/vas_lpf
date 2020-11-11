#pragma once

#include <string>
#include <map>
#include "vasDefined.h"
#include "vasServiceHandler.h"

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

    /* * * * * * * 3.服务接口 * * * * * * */

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
    vasEventHandler                              *m_pEventHandler;
    vasServiceHandler                            *m_pServiceHandler;
    std::map<std::string, VAS::vasPluginInfo_St>  m_pluginsMap;
};

template<typename SERVICE_T>
SERVICE_T VAS::vasPluginContext::getService(const std::string &svcId)
{
    return m_pServiceHandler->getService<SERVICE_T>(svcId);
}

} /*namespace VAS*/