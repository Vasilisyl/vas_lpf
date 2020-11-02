#pragma once

#include <functional>
#include <map>
#include <string>
#include "vasDefined.h"
#include "vasVariant.h"

namespace VAS {

typedef std::map<std::string, VAS::vasVariant> vasProperty;
typedef std::function<void(vasProperty)>       vasEventCallBack;

/**
 * @brief vasEvent 框架事件类
 */
class vasEvent
{
    VAS_DISABLED_COPY(vasEvent)
public:
    vasEvent();
    vasEvent(void *pObj, vasEventCallBack func);
    virtual ~vasEvent();

    void registEvent(void *pObj, vasEventCallBack func);
    void unregistEvent();
    bool isValid();

private:
    void             *m_pObj;
    vasEventCallBack  m_pFunc;
};


} /*namespace VAS*/