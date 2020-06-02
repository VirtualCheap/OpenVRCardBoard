#ifndef WATCHDOGDRIVER_H
#define WATCHDOGDRIVER_H

#include <openvr_driver.h>
#include <thread>

namespace VirtualCheap{
    class WatchdogDriver: public vr::IVRWatchdogProvider{
    public:
        WatchdogDriver();
        virtual ~WatchdogDriver();

        // vr::IVRWatchdogProvider
        virtual vr::EVRInitError Init(vr::IVRDriverContext *p_DriverContext);
        virtual void Cleanup();

    private:
        std::thread *m_pWatchdogThread;
    };
}

#endif // WATCHDOGDRIVER_H
