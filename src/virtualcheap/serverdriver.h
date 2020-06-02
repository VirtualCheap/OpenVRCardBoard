#ifndef SERVERDRIVER_H
#define SERVERDRIVER_H

#include <openvr_driver.h>

#include "controllerdriver.h"
#include "devicedriver.h"
#include "logger.h"

namespace VirtualCheap{
    class ServerDriver: public vr::IServerTrackedDeviceProvider{
    public:
        virtual ~ServerDriver();

        // vr::IServerTrackedDeviceProvider
        virtual vr::EVRInitError Init(vr::IVRDriverContext* p_driverContext);
        virtual void Cleanup();
        virtual const char* const* GetInterfaceVersions();
        virtual void RunFrame();
        virtual bool ShouldBlockStandbyMode();
        virtual void EnterStandby();
        virtual void LeaveStandby();

    private:
        // TODO look at
        DeviceDriver* m_deviceDriver = nullptr;
        ControllerDriver* m_controllerDriver = nullptr;
    };
}

#endif // SERVERDRIVER_H
