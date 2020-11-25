#include <iostream>
#include <vector>
#include <cstdlib>
#include "vasPluginContext.h"

#ifdef __cplusplus
extern "C" {
#endif
#include <unistd.h>
#ifdef __cplusplus
}
#endif

/*批量安装插件*/
std::vector<std::string> installPlugins(const std::vector<std::string> &pluginPathVec);

/*批量启动插件*/
void startPlugins(const std::vector<std::string> &pluginIdVec);

/*批量停止插件*/
void stopPlugins(const std::vector<std::string> &pluginIdVec);

/*批量卸载插件*/
void uninstallPlugins(const std::vector<std::string> &pluginIdVec);
#include <thread>
int main(int argc, char *argv[])
{
    std::cout << "install ......" << std::endl;

    std::vector<std::string> pluginPathVec;
    const char *pWorkPath = get_current_dir_name();
#ifndef NDEBUG /*DEBUG*/
    pluginPathVec.push_back(std::string(pWorkPath) + "/../plugins/libplugin_demod.so"); /*测试插件plugin.demo*/
    pluginPathVec.push_back(std::string(pWorkPath) + "/../plugins/libplugin_testd.so"); /*测试插件plugin.test*/
#else /*RELEASE*/
    pluginPathVec.push_back(std::string(pWorkPath) + "/../plugins/libplugin_demo.so"); /*测试插件plugin.demo*/
    pluginPathVec.push_back(std::string(pWorkPath) + "/../plugins/libplugin_test.so"); /*测试插件plugin.test*/
#endif

    try {

        /*安装插件*/
        std::vector<std::string> pluginIdVec = ::installPlugins(pluginPathVec);
        if (pluginIdVec.empty()) {
            return -1;
        }

        /*启动插件*/
        /*plugin.test插件将在启动时通过触发事件的方式，完成与plugin.demo插件之间的数据交互*/
        ::startPlugins(pluginIdVec);

        /*停止插件*/
        ::stopPlugins(pluginIdVec);

        /*卸载插件*/
        ::uninstallPlugins(pluginIdVec);

    } catch (const VAS::vasException &e) {
        std::cout << e.what() << std::endl;
        return -1;
    }
    
    return 0;
}

std::vector<std::string> installPlugins(const std::vector<std::string> &pluginPathVec)
{
    std::string err;
    std::vector<std::string> pluginIdVec;
    std::string pluginId;
    for (const std::string &pluginPath : pluginPathVec) {
        pluginId = VAS_PLUGIN_CONTEXT->install(pluginPath);
        pluginIdVec.push_back(pluginId);
    }
    return pluginIdVec;
}

void startPlugins(const std::vector<std::string> &pluginIdVec)
{
    std::string err;
    for (const std::string &pluginId : pluginIdVec) {
        VAS_PLUGIN_CONTEXT->startPlugin(pluginId);
    }
}

void stopPlugins(const std::vector<std::string> &pluginIdVec)
{
    std::string err;
    for (const std::string &pluginId : pluginIdVec) {
        VAS_PLUGIN_CONTEXT->stopPlugin(pluginId);
    }
}

void uninstallPlugins(const std::vector<std::string> &pluginIdVec)
{
    std::string err;
    for (const std::string &pluginId : pluginIdVec) {
        VAS_PLUGIN_CONTEXT->uninstall(pluginId);
    }
}