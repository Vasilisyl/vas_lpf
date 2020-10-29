#pragma once

#include "vasDefined.h"

namespace VAS {

/**
 * @brief 事件管理器类
 */

/*管理一个组的事件*/
class vasEventHandler final
{
    VAS_DISABLED_COPY(vasEventHandler)
public:
    vasEventHandler();
    ~vasEventHandler();

    // void setGroupKey();
    // void addEventKey();
};

} /*namespace VAS*/