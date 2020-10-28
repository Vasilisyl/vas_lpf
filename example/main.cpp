#include <iostream>
#include "vasPluginContext.h"

int main(int argc, char *argv[])
{
    std::cout << "install ......" << std::endl;
    
    /*./plugin_test/build/libplugin_test.so*/
    std::string errStr;
    std::string pluginId = VAS_PLUGIN_CONTEXT->install("./plugin_test/build/libplugin_test.so", &errStr);
    
    if (pluginId.empty()) {
        std::cout << "install failed ! reason: " << errStr << std::endl;
        return -1;
    }
    
    do {

        std::cout << "starting ......" << std::endl;
        if (!VAS_PLUGIN_CONTEXT->startPlugin(pluginId, &errStr)) {
            std::cout << "start failed ! reason: " << errStr << std::endl;
            break; /*to uninstall*/
        }
        
        std::cout << "stopping ......" << std::endl;
        if (!VAS_PLUGIN_CONTEXT->stopPlugin(pluginId, &errStr)) {
            std::cout << "stop failed ! reason: " << errStr << std::endl;
            break; /*to uninstall*/
        }

    } while (0);
    
    std::cout << "uninstalling ......" << std::endl;
    if (!VAS_PLUGIN_CONTEXT->uninstall(pluginId, &errStr)) {
        std::cout << "uninstall failed ! reason: " << errStr << std::endl;
        return -1;
    }

    std::cout << "finished !" << std::endl;
    
    return 0;
}