#pragma once

#include <string>
#include "vasDefined.h"

/**
 * vasPlugin插件的创建
 * 1.插件都必须从vasPlugin类派生，并且实现start和stop接口；
 * 2.插件在头文件的声明中使用VAS_PLUGIN宏来替代插件的构造函数，例如：VAS_PLUGIN(PluginTest, "plugin.test")，其中PluginTest为类名，"plugin.test"为该插件ID；
 * 3.插件在源文件的尾部必须使用VAS_REGIST_PLUGIN_ID宏，例如：VAS_REGIST_PLUGIN_ID(PluginTest, "plugin.test")，其中PluginTest为类名，"plugin.test"为该插件ID；
 * 4.当框架启动插件时，框架将会调用插件的start接口；
 * 5.当框架停止插件时，框架将会调用插件的stop接口；
 * 
 * 例如：
 * 有一个ID为plugin.test的插件，该插件类名为PluginTest
 * 那么plugin_test.h的写法如下：
 * 
 * * * * * * plugin_test.h * * * * * *
 * 
 * #include "vasPlugin.h"
 * 
 * class PluginTest : public vasPlugin
 * {
 * public:
 *     VAS_PLUGIN(PluginTest, "plugin.test") // VAS_PLUGIN宏替代插件构造函数
 * 
 *     virtual void start() override;
 *     virtual void stop() override;
 * };
 * 
 * * * * * * plugin_test.cpp * * * * * *
 *
 * #include "plugin_test.h" 
 *
 * void PluginTest::start()
 * {
 *     // 插件启动时需要进行的业务
 * }
 * 
 * void PluginTest::stop()
 * {
 *     // 插件停止时需要进行的业务
 * }
 * 
 * VAS_REGIST_PLUGIN_ID(PluginTest) // VAS_REGIST_PLUGIN_ID宏作为源文件的结尾
 * 
 */

namespace VAS {

/**
 * @brief vasPlugin 插件接口类
 */
VAS_USER_INTERFACE_CLASS vasPlugin
{
    VAS_DISABLED_COPY(vasPlugin)
public:
    vasPlugin(const std::string &pgId)
        : m_pgId(pgId) {}
    virtual ~vasPlugin() {}
    
    /**
     * @brief  启动接口
     *         vasPlugin插件派生类重写start()，当该插件被启动时框架将会调用start()
     */
    virtual void start() = 0;

    /**
     * @brief  stop 停止接口
     *         vasPlugin插件派生类重写stop()，当该插件被停止时框架将会调用stop()
     */
    virtual void stop() = 0;
    
    /**
     * @brief  getPluginId 获取插件ID
     * @return std::string 插件ID
     */
    const std::string &getPluginId() const { return m_pgId; }
    
private:
    const std::string m_pgId;
};

} /*namespace VAS*/