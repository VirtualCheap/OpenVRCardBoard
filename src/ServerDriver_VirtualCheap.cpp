#include "ServerDriver_VirtualCheap.h"

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
ServerDriver_VirtualCheap::ServerDriver_VirtualCheap()
    : m_pNullHmdLatest( NULL )
    , m_bEnableNullDriver( false )
{
}


const char * const *GetInterfaceVersions() { return vr::k_InterfaceVersions; }
bool ShouldBlockStandbyMode()  { return false; }
void EnterStandby()  {}
void LeaveStandby()  {}


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
