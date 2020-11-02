#pragma once

#include <map>
#include "vasDefined.h"

namespace VAS {

class vasEvent;

typedef std::map<std::string, vasEvent *> vasEventGroup;

/**
 * @brief vasEventHandler 事件管理器类
 */
class vasEventHandler final
{
    VAS_DISABLED_COPY(vasEventHandler)
public:
    vasEventHandler();
    ~vasEventHandler();

    void setEvent();

private:
    std::multimap<std::string, vasEventGroup> m_eventGroupMap;
};

} /*namespace VAS*/