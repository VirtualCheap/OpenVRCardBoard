#include <thread>
#include <openvr_driver.h>

#include "driverlog.h"

using namespace vr;

#ifndef WATCHDOGDRIVER_VIRTUALCHEAP_H
#define WATCHDOGDRIVER_VIRTUALCHEAP_H


class WatchdogDriver_VirtualCheap : public IVRWatchdogProvider
{
public:
    WatchdogDriver_VirtualCheap()
    {
        m_pWatchdogThread = nullptr;
    }

    virtual EVRInitError Init( vr::IVRDriverContext *pDriverContext ) ;
    virtual void Cleanup() ;

private:
    std::thread *m_pWatchdogThread;
};

#endif // WATCHDOGDRIVER_VIRTUALCHEAP_H
