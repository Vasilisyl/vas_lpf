#pragma once

#include <string>

#ifndef VAS_DISABLED_COPY
    #define VAS_DISABLED_COPY(ClassName) \
        ClassName(const ClassName &) = delete; \
        ClassName &operator=(const ClassName &) = delete;
#endif
        
/*vasPlugins Construct*/
#ifndef VAS_CONSTRUCT_PLUGIN
    #define VAS_CONSTRUCT_PLUGIN(ClassName, pgId) \
        ClassName(const std::string &pgId) : vasPlugins(pgId) {}
#endif

/*Add VAS_REGIST_PLUGIN_ID to the end of CPP file*/
#ifndef VAS_REGIST_PLUGIN_ID
    #define VAS_REGIST_PLUGIN_ID(ClassName, pgId) \
        extern "C" vasPlugins *createPlugin() \
        { \
            return new ClassName(pgId); \
        }
#endif

/*error set*/
#ifndef VAS_ERROR_SET
    #define VAS_ERROR_SET(pStr, error) \
        if (pStr && error) { *pStr = std::string("[ERROR] ") + error; }
#endif

/*info set*/
#ifndef VAS_INFO_SET
    #define VAS_INFO_SET(pStr, info) \
        if (pStr && info) { *pStr = std::string("[INFO] ") + info; }
#endif

class  vasPlugin;

namespace VAS {
/*enums*/
enum vasPluginState_Em {
    VAS_PS_UNINSTALLED = 0,
    VAS_PS_INSTALLED,
    VAS_PS_STARTING,
    VAS_PS_STOPPING,
};

/*structs*/
struct vasPluginInfo_St
{
    vasPluginInfo_St()
        : _pHandle(nullptr), _pPlugin(nullptr) {}
    
    void              *_pHandle;
    std::string        _pluginPath;
    vasPlugin         *_pPlugin;
    vasPluginState_Em  _state;
};

} /*namespace VAS*/
