#include <iostream>
#include "../vasPluginContext.h"

int main(int argc, char *argv[])
{
    std::cout << "install ......" << std::endl;
    
    /*./plugin_test/build/libplugin_test.so*/
    std::string pluginId = VAS_PLUGIN_CONTEXT->install("");
    
    if (pluginId.empty()) {
        std::cout << "install failed !" << std::endl;
        return -1;
    }
    
    std::cout << "starting ......" << std::endl;
    if (!VAS_PLUGIN_CONTEXT->startPlugin(pluginId)) {
        std::cout << "start failed !" << std::endl;
        VAS_PLUGIN_CONTEXT->uninstall(pluginId);
        return -1;
    }
    
    std::cout << "stopping ......" << std::endl;
    if (!VAS_PLUGIN_CONTEXT->stopPlugin(pluginId)) {
        std::cout << "stop failed !" << std::endl;
        VAS_PLUGIN_CONTEXT->uninstall(pluginId);
        return -1;
    }
    
    std::cout << "uninstalling ......" << std::endl;
    if (!VAS_PLUGIN_CONTEXT->uninstall(pluginId)) {
        std::cout << "uninstall failed !" << std::endl;
        return -1;
    }
    
    return 0;
}
