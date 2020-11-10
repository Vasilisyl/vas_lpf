#pragma once

#include <functional>
#include "vasDefined.h"

namespace VAS {

#ifndef VAS_EVENT_G
    #define VAS_EVENT_G(func) \
        VAS::vasEvent(std::bind(func, std::placeholders::_1))
#endif /*VAS_EVENT_G*/

#ifndef VAS_EVENT_M
    #define VAS_EVENT_M(func, obj) \
        VAS::vasEvent(std::bind(func, obj, std::placeholders::_1))
#endif /*VAS_EVENT_M*/

/**
 * @brief vasEvent 事件类
 */
VAS_USER_CLASS vasEvent VAS_DISABLED_INHERIT
{
public:
    vasEvent() = default;
    vasEvent(const VAS::vasEvent &e) { this->m_eventFunc = e.m_eventFunc; }
    vasEvent(VAS::vasEvent &&e) { this->m_eventFunc = e.m_eventFunc; }
    vasEvent(const std::function<void(VAS::vasProperty)> &func) : m_eventFunc(func) {}
    ~vasEvent() = default;

    inline void setEvent(const std::function<void(VAS::vasProperty)> &eventFunc) { m_eventFunc = eventFunc; }

    VAS::vasEvent &operator=(const VAS::vasEvent &e) { this->m_eventFunc = e.m_eventFunc; return *this; }
    void operator()(VAS::vasProperty property) { return m_eventFunc(property); }

private:
    std::function<void(VAS::vasProperty)> m_eventFunc;

};

} /*namespace VAS*/