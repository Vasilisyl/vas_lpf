#pragma once

#include <map>
#include <mutex>
#include "vasDefined.h"
#include "vasVariant.h"

namespace VAS {

class vasPluginContext;
class vasEvent;

/**
 * @brief vasEventHandler 事件管理器类
 */
VAS_PRIVATE_IMPL_CLASS vasEventHandler VAS_DISABLED_INHERIT
{
    VAS_DISABLED_COPY(vasEventHandler)
    VAS_DECLARE_FRIEND_CONTEXT

    vasEventHandler() noexcept;
    ~vasEventHandler() noexcept;

    /**
     * @brief  triggerEvent  触发事件，当事件触发时，对应事件组中的所有注册的事件将会被调用，并获得参数列表property
     * @param  eventGroupKey 事件组唯一键值，一个事件组中包含一个或多个事件
     * @param  property      触发事件时需要传递的参数列表，vasProperty中可填充多个参数对象，以不同的参数键值区分
     */
    void triggerEvent(const std::string &eventGroupKey, VAS::vasProperty property) noexcept;

    /**
     * @brief  triggerEvent  触发事件，当事件触发时，对应事件组中的所有注册的事件将会被调用，并获得参数列表property
     * @param  eventGroupKey 事件组唯一键值，一个事件组中包含一个或多个事件
     * @param  eventKey      事件键值，在同一个事件组中，一个事件键值与一个事件一一对应
     * @param  property      触发事件时需要传递的参数列表，vasProperty中可填充多个参数对象，以不同的参数键值区分
     */
    void triggerEvent(const std::string &eventGroupKey, const std::string &eventKey, VAS::vasProperty property) noexcept;

    /**
     * @brief  registEvent    注册事件，当任何地方触发事件时，该事件组中的所有注册的事件将会被调用，并获得参数列表property
     * @note                  （注意：registEvent应该与unregistEvent一一对应，如同new和delete的关系，
     *                               registEvent的调用者应当在不需要响应事件的触发时或事件所属对象析构释放时调用unregistEvent取消事件的注册）
     * @param  eventGroupKey  事件组唯一键值，一个事件组中包含一个或多个事件
     * @param  eventKey       事件键值，在同一个事件组中，一个事件键值与一个事件一一对应
     * @param  event          事件
     */
    void registEvent(const std::string &eventGroupKey, const std::string &eventKey, VAS::vasEvent event) noexcept;

    /**
     * @brief  unregistEvent  取消事件的注册，取消指定事件的注册
     * @note                  （注意：registEvent应该与unregistEvent一一对应，如同new和delete的关系，
     *                               registEvent的调用者应当在不需要响应事件的触发时或事件所属对象析构释放时调用unregistEvent取消事件的注册）
     * @param  eventGroupKey  事件组唯一键值，一个事件组中包含一个或多个事件
     * @param  eventKey       事件键值，在同一个事件组中，一个事件键值与一个事件一一对应
     */
    void unregistEvent(const std::string &eventGroupKey, const std::string &eventKey) noexcept;

private:

    typedef std::map<std::string, VAS::vasEvent>                        vasEventGroup;
    typedef std::map<std::string, VAS::vasEventHandler::vasEventGroup>  vasEventManager;

    VAS::vasEventHandler::vasEventManager m_eventMgr;
    std::mutex m_mutex;
};

} /*namespace VAS*/