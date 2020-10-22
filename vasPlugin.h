#pragma once

#include <string>
#include "vasDefined.h"

class vasPlugin
{
    VAS_DISABLED_COPY(vasPlugin)
public:
    vasPlugin(const std::string &pgId)
        : m_pgId(pgId) {}
    virtual ~vasPlugin() {}
    
    virtual void start() = 0;
    virtual void stop() = 0;
    
    const std::string &getPluginId() const { return m_pgId; }
    
private:
    const std::string m_pgId;
};
