#include "logger.h"

#include <stdio.h>
#include <stdarg.h>

using namespace VirtualCheap;

bool Logger::InitDriverLog( vr::IVRDriverLog *p_driverLog ){
    if(s_driverLog){
		return false;
    }
    s_driverLog = p_driverLog;

    return s_driverLog != nullptr;
}

void Logger::CleanupDriverLog(){
    s_driverLog = nullptr;
}

void Logger::DriverLog(const char *p_msgFormat, ...){
    va_list args;
    va_start(args, p_msgFormat);

    char buf[1024];
    vsnprintf(buf, sizeof(buf), p_msgFormat, args);

    if(s_driverLog){
        s_driverLog->Log(buf);
    }

    va_end(args);
}


void Logger::DebugDriverLog(const char *p_msgFormat, ...){
#ifndef NDEBUG
    Logger::DriverLog(p_msgFormat);
#endif
}


