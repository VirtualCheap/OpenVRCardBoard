#ifndef DRIVERLOG_H
#define DRIVERLOG_H

#include <string>
#include <openvr_driver.h>

namespace VirtualCheap {
    class Logger {
    private:
        static vr::IVRDriverLog* s_driverLog;

    public:
        static bool InitDriverLog(vr::IVRDriverLog *p_driverLog);
        static void CleanupDriverLog();

        static void DriverLog(const char *p_msgFormat, ...);
        static void DebugDriverLog(const char *p_msgFormat, ...);
    };
}

#endif // DRIVERLOG_H
