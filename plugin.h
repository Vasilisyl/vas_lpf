#pragma once
#include <mutex>

/*
 *context加载.so成功之后，通过动态库符号调用Plugin的getInstance获取到实例
 */

#define DELETE_COPY(ClassName) \
    ClassName(const ClassName &) = delete; \
    ClassName &operator=(const ClassName &) = delete;
    
#define CREATE_INSTANCE(ClassName, pgId) \
    static Plugin *getInstance() \
    { \
        static ClassName *s_pInstance = nullptr; \
        static std::mutex s_mutex; \
        std::unique_lock<std::mutex> lock(s_mutex); \
        if (!s_pInstance) { s_pInstance = new ClassName(pgId); } \
        return s_pInstance; \
    }

class Plugin
{
    DELETE_COPY(Plugin)
public:
    Plugin(const std::string &pgId)
        : m_pgId(pgId) {}
    virtual ~Plugin() {}
    
    virtual void start() = 0;
    virtual void stop() = 0;
    
    inline const std::string &getPluginId() const { return m_pgId; }
private:
    const std::string m_pgId;
};
