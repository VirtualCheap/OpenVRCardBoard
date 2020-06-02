#include <cstring>
#include <openvr_driver.h>

#include "virtualcheap/serverdriver.h"
#include "virtualcheap/watchdogdriver.h"

// Null varables of the drivers
extern VirtualCheap::ServerDriver* g_virtualCheepNullServerDriver;
extern VirtualCheap::WatchdogDriver* g_virtualCheepNullWatchdogDriver;


// Driver factory function
#if defined(_WIN32)
#define HMD_DLL_EXPORT extern "C" __declspec( dllexport )
#elif defined(__GNUC__) || defined(COMPILER_GCC) || defined(__APPLE__)
#define HMD_DLL_EXPORT extern "C" __attribute__((visibility("default")))
#else
#error "Unsupported Platform."
#endif

HMD_DLL_EXPORT
void* HmdDriverFactory(const char *pInterfaceName, int *pReturnCode){
    if(strcmp(vr::IServerTrackedDeviceProvider_Version, pInterfaceName) == 0){
        return g_virtualCheepNullServerDriver;
    }
    if(strcmp(vr::IVRWatchdogProvider_Version, pInterfaceName) == 0){
        return g_virtualCheepNullWatchdogDriver;
    }

    if(pReturnCode){
        *pReturnCode = vr::VRInitError_Init_InterfaceNotFound;
    }
    return nullptr;
}
