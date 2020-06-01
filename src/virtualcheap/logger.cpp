#include "logger.h"

#include <stdio.h>
#include <stdarg.h>

using namespace VirtualCheap;

bool Logger::InitDriverLog( vr::IVRDriverLog *pDriverLog ){
    if(driverLog){
		return false;
    }
    driverLog = pDriverLog;

    return driverLog != nullptr;
}

void Logger::CleanupDriverLog(){
    driverLog = nullptr;
}

void Logger::DriverLog(const char *pMsgFormat, ...){
    va_list args;
    va_start(args, pMsgFormat);

    char buf[1024];
    vsnprintf(buf, sizeof(buf), pMsgFormat, args);

    if(driverLog){
        driverLog->Log(buf);
    }

    va_end(args);
}


void Logger::DebugDriverLog(const char *pMsgFormat, ...){
#ifndef NDEBUG
    Logger::DriverLog(pMsgFormat);
#endif
}


