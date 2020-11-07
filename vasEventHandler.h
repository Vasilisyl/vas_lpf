#pragma once

#include <map>
#include <mutex>
#include "vasDefined.h"
#include "vasVariant.h"

namespace VAS {

class vasPluginContext;

/**
 * @brief vasEventHandler 事件管理器类
 */
VAS_PRIVATE_IMPL_CLASS vasEventHandler final
{
    VAS_DISABLED_COPY(vasEventHandler)
    VAS_DECLARE_FRIEND_CONTEXT

    vasEventHandler();
    ~vasEventHandler();

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

    typedef std::map<std::string, VAS::vasEvent>                        vasEventGroup;
    typedef std::map<std::string, VAS::vasEventHandler::vasEventGroup>  vasEventManager;

    VAS::vasEventHandler::vasEventManager m_eventMgr;
    std::mutex m_mutex;
};

} /*namespace VAS*/