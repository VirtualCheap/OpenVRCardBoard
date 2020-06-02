#include "watchdogdriver.h"

#include "logger.h"

using namespace VirtualCheap;

// TODO move to class
bool g_bExiting = false;
void WatchdogThreadFunction(){
    while (!g_bExiting){
#if defined( _WINDOWS )
        // on windows send the event when the Y key is pressed.
        if ( (0x01 & GetAsyncKeyState( 'Y' )) != 0 )
        {
            // Y key was pressed.
            vr::VRWatchdogHost()->WatchdogWakeUp( vr::TrackedDeviceClass_HMD );
        }
        std::this_thread::sleep_for( std::chrono::microseconds( 500 ) );
#else
        // for the other platforms, just send one every five seconds
        std::this_thread::sleep_for( std::chrono::seconds( 5 ) );
        vr::VRWatchdogHost()->WatchdogWakeUp( vr::TrackedDeviceClass_HMD );
#endif
    }
}

WatchdogDriver::WatchdogDriver(){
    m_pWatchdogThread = nullptr;
}

WatchdogDriver::~WatchdogDriver(){}

vr::EVRInitError WatchdogDriver::Init(vr::IVRDriverContext *p_DriverContext){
    VR_INIT_WATCHDOG_DRIVER_CONTEXT(p_DriverContext)
    Logger::InitDriverLog(vr::VRDriverLog());

    // Watchdog mode on Windows starts a thread that listens for the 'Y' key on the keyboard to
    // be pressed. A real driver should wait for a system button event or something else from the
    // the hardware that signals that the VR system should start up.
    g_bExiting = false;
    m_pWatchdogThread = new std::thread(WatchdogThreadFunction);
    if (!m_pWatchdogThread){
        Logger::DriverLog("Unable to create watchdog thread\n");
        return vr::VRInitError_Driver_Failed;
    }

    return vr::VRInitError_None;
}

void WatchdogDriver::Cleanup(){}
