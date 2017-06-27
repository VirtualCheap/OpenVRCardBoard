#include <openvr_driver.h>

#include "WatchdogDriver_VirtualCheap.h"
#include "ServerDriver_VirtualCheap.h"

#if defined( _WINDOWS )
#include <Windows.h>
#endif

using namespace vr;

#if defined(_WIN32)
#define strcasecmp stricmp
#define HMD_DLL_EXPORT extern "C" __declspec( dllexport )
#define HMD_DLL_IMPORT extern "C" __declspec( dllimport )
#elif defined(__GNUC__) || defined(COMPILER_GCC) || defined(__APPLE__)
#define HMD_DLL_EXPORT extern "C" __attribute__((visibility("default")))
#define HMD_DLL_IMPORT extern "C"
#else
#error "Unsupported Platform."
#endif

#ifndef DRIVER_VIRTUALCHEAP_H
#define DRIVER_VIRTUALCHEAP_H
WatchdogDriver_VirtualCheap g_watchdogDriverVirtualCheap;
ServerDriver_VirtualCheap g_serverDriverNull;
HMD_DLL_EXPORT void *HmdDriverFactory( const char *pInterfaceName, int *pReturnCode );


#endif // DRIVER_VIRTUALCHEAP_H
