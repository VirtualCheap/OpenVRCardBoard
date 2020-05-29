#include "virtualcheap_logger.h"

#include <stdio.h>
#include <stdarg.h>

bool VirtualCheapLogger::InitDriverLog( vr::IVRDriverLog *pDriverLog ){
    if(driverLog){
		return false;
    }
    driverLog = pDriverLog;

    return driverLog != nullptr;
}

void VirtualCheapLogger::CleanupDriverLog(){
    driverLog = nullptr;
}

void VirtualCheapLogger::DriverLog(const char *pMsgFormat, ...){
    va_list args;
    va_start(args, pMsgFormat);

    char buf[1024];
    vsnprintf(buf, sizeof(buf), pMsgFormat, args);

    if(driverLog){
        driverLog->Log(buf);
    }

    va_end(args);
}


void VirtualCheapLogger::DebugDriverLog(const char *pMsgFormat, ...){
#ifndef NDEBUG
    VirtualCheapLogger::DriverLog(pMsgFormat);
#endif
}


