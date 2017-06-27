#include <openvr_driver.h>
#include "devicedriver_virtualcheap.h"

using namespace vr;

#ifndef SERVERDRIVER_VIRTUALCHEAP_H
#define SERVERDRIVER_VIRTUALCHEAP_H


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

#endif // SERVERDRIVER_VIRTUALCHEAP_H
