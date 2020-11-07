#include <iostream>
#include "vasPluginContext.h"

using namespace VAS;

void test(const std::string &pluginPath);

int main(int argc, char *argv[])
{
    std::cout << "install ......" << std::endl;

    /*测试插件plugin_demo*/
    test("./plugin_demo/build/libplugin_demo.so");
    /*测试插件plugin_test*/
    test("./plugin_test/build/libplugin_test.so");
    
    return 0;
}

void test(const std::string &pluginPath)
{
    std::cout << "[TEST] install plugin (" << pluginPath << ") ......" << std::endl;

    std::string errStr;
    /*安装插件*/
    std::string pluginId = VAS_PLUGIN_CONTEXT->install(pluginPath, &errStr);
    
    if (pluginId.empty()) {
        std::cout << "install failed ! reason: " << errStr << std::endl;
        return;
    }
    
    do {

        std::cout << "starting ......" << std::endl;
        /*启动插件*/
        if (!VAS_PLUGIN_CONTEXT->startPlugin(pluginId, &errStr)) {
            std::cout << "start failed ! reason: " << errStr << std::endl;
            break; /*to uninstall*/
        }
        
        std::cout << "stopping ......" << std::endl;
        /*停止插件*/
        if (!VAS_PLUGIN_CONTEXT->stopPlugin(pluginId, &errStr)) {
            std::cout << "stop failed ! reason: " << errStr << std::endl;
            break; /*to uninstall*/
        }

    } while (0);
    
    std::cout << "uninstalling ......" << std::endl;
    /*卸载插件*/
    if (!VAS_PLUGIN_CONTEXT->uninstall(pluginId, &errStr)) {
        std::cout << "uninstall failed ! reason: " << errStr << std::endl;
        return;
    }

    std::cout << "[TEST] finished !" << std::endl;
    return;
}