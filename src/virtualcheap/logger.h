#ifndef DRIVERLOG_H
#define DRIVERLOG_H

#include <string>
#include <openvr_driver.h>
namespace VirtualCheap {
    class Logger {
    private:
        static vr::IVRDriverLog* driverLog;

    public:
        static bool InitDriverLog(vr::IVRDriverLog *pDriverLog);
        static void CleanupDriverLog();

        static void DriverLog(const char *format, ...);
        static void DebugDriverLog(const char *format, ...);
    };
}

#endif // DRIVERLOG_H
