//============ Copyright (c) Valve Corporation, All rights reserved. ============

#include <openvr_driver.h>
#include "driverlog.h"

#include <string.h>
#include <thread>

#include "watchdogdriver_virtualcheap.h"
#include "devicedriver_virtualcheap.h"

#if defined( _WINDOWS )
#include <Windows.h>
#endif

using namespace vr;


#if defined(_WIN32)
#define HMD_DLL_EXPORT extern "C" __declspec( dllexport )
#define HMD_DLL_IMPORT extern "C" __declspec( dllimport )
#elif defined(__GNUC__) || defined(COMPILER_GCC) || defined(__APPLE__)
#define HMD_DLL_EXPORT extern "C" __attribute__((visibility("default")))
#define HMD_DLL_IMPORT extern "C" 
#else
#error "Unsupported Platform."
#endif

inline void HmdMatrix_SetIdentity( HmdMatrix34_t *pMatrix )
{
	pMatrix->m[0][0] = 1.f;
	pMatrix->m[0][1] = 0.f;
	pMatrix->m[0][2] = 0.f;
	pMatrix->m[0][3] = 0.f;
	pMatrix->m[1][0] = 0.f;
	pMatrix->m[1][1] = 1.f;
	pMatrix->m[1][2] = 0.f;
	pMatrix->m[1][3] = 0.f;
	pMatrix->m[2][0] = 0.f;
	pMatrix->m[2][1] = 0.f;
	pMatrix->m[2][2] = 1.f;
	pMatrix->m[2][3] = 0.f;
}

WatchdogDriver_VirtualCheap g_watchdogDriverNull;

class ServerDriver_VirtualCheap: public IServerTrackedDeviceProvider
{
public:
    ServerDriver_VirtualCheap()
        : m_pNullHmdLatest( NULL )
        , m_bEnableNullDriver( false )
    {
    }

    virtual EVRInitError Init( vr::IVRDriverContext *pDriverContext ) ;
    virtual void Cleanup() ;
    virtual const char * const *GetInterfaceVersions();
    virtual void RunFrame() ;
    virtual bool ShouldBlockStandbyMode();
    virtual void EnterStandby();
    virtual void LeaveStandby();

private:
    DeviceDriver_VirtualCheap *m_pNullHmdLatest;

    bool m_bEnableNullDriver;
};

EVRInitError ServerDriver_VirtualCheap::Init( vr::IVRDriverContext *pDriverContext )
{
    VR_INIT_SERVER_DRIVER_CONTEXT( pDriverContext );
    InitDriverLog( vr::VRDriverLog() );

    m_pNullHmdLatest = new DeviceDriver_VirtualCheap();
    vr::VRServerDriverHost()->TrackedDeviceAdded( m_pNullHmdLatest->GetSerialNumber().c_str(), vr::TrackedDeviceClass_HMD, m_pNullHmdLatest );
    return VRInitError_None;
}

void ServerDriver_VirtualCheap::Cleanup()
{
    CleanupDriverLog();
    delete m_pNullHmdLatest;
    m_pNullHmdLatest = NULL;
}


void ServerDriver_VirtualCheap::RunFrame()
{
    if ( m_pNullHmdLatest )
    {
        m_pNullHmdLatest->RunFrame();
    }
}

const char * const *GetInterfaceVersions() { return vr::k_InterfaceVersions; }
bool ShouldBlockStandbyMode()  { return false; }
void EnterStandby()  {}
void LeaveStandby()  {}


ServerDriver_VirtualCheap g_serverDriverNull;

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
HMD_DLL_EXPORT void *HmdDriverFactory( const char *pInterfaceName, int *pReturnCode )
{
	if( 0 == strcmp( IServerTrackedDeviceProvider_Version, pInterfaceName ) )
	{
		return &g_serverDriverNull;
	}
	if( 0 == strcmp( IVRWatchdogProvider_Version, pInterfaceName ) )
	{
		return &g_watchdogDriverNull;
	}

	if( pReturnCode )
		*pReturnCode = VRInitError_Init_InterfaceNotFound;

	return NULL;
}
