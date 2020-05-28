#include "watchdogdriver_virtualcheap.h"

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------

WatchdogDriver_VirtualCheap::WatchdogDriver_VirtualCheap()
{
    m_pWatchdogThread = nullptr;
}

bool g_bExiting = false;

void WatchdogThreadFunction(  )
{
    while ( !g_bExiting )
    {
#if defined( _WINDOWS )
        // on windows send the event when the Y key is pressed.
        if ( (0x01 & GetAsyncKeyState( 'Y' )) != 0 )
        {
            // Y key was pressed.
            vr::VRWatchdogHost()->WatchdogWakeUp( vr::ETrackedDeviceClass() );
        }
        std::this_thread::sleep_for( std::chrono::microseconds( 500 ) );
#else
        // for the other platforms, just send one every five seconds
        std::this_thread::sleep_for( std::chrono::seconds( 5 ) );
        vr::VRWatchdogHost()->WatchdogWakeUp( vr::ETrackedDeviceClass() );
#endif
    }
}

EVRInitError WatchdogDriver_VirtualCheap::Init( vr::IVRDriverContext *pDriverContext )
{
    VR_INIT_WATCHDOG_DRIVER_CONTEXT( pDriverContext );
    InitDriverLog( vr::VRDriverLog() );

    // Watchdog mode on Windows starts a thread that listens for the 'Y' key on the keyboard to
    // be pressed. A real driver should wait for a system button event or something else from the
    // the hardware that signals that the VR system should start up.
    g_bExiting = false;
    m_pWatchdogThread = new std::thread( WatchdogThreadFunction );
    if ( !m_pWatchdogThread )
    {
        DriverLog( "Unable to create watchdog thread\n");
        return VRInitError_Driver_Failed;
    }

    return VRInitError_None;
}


void WatchdogDriver_VirtualCheap::Cleanup()
{
    g_bExiting = true;
    if ( m_pWatchdogThread )
    {
        m_pWatchdogThread->join();
        delete m_pWatchdogThread;
        m_pWatchdogThread = nullptr;
    }

    CleanupDriverLog();
}
