#include <openvr_driver.h>

#include "DeviceDriver_VirtualCheap.h"

using namespace vr;
#ifndef SERVERDRIVERVIRTUALCHEAP_H
#define SERVERDRIVERVIRTUALCHEAP_H


class ServerDriver_VirtualCheap: public IServerTrackedDeviceProvider
{
public:
    ServerDriver_VirtualCheap();

    virtual EVRInitError Init( vr::IVRDriverContext *pDriverContext );
    virtual void Cleanup();
    virtual const char * const *GetInterfaceVersions();
    virtual void RunFrame();
    virtual bool ShouldBlockStandbyMode();
    virtual void EnterStandby();
    virtual void LeaveStandby();

private:
    DeviceDriver_VirtualCheap *m_pNullHmdLatest;

    bool m_bEnableNullDriver;
};

#endif // SERVERDRIVERVIRTUALCHEAP_H
