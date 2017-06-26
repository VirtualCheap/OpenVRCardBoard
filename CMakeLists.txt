cmake_minimum_required(VERSION 3.3)
project(VirtualCheap C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_SHARED_LIBRARY_PREFIX "")

include_directories(openvr/headers/)

set(SOURCE_FILES
        src/driver_VirtualCheap.cpp
        src/driver_VirtualCheap.h
        src/WatchdogDriver_VirtualCheap.cpp
        src/WatchdogDriver_VirtualCheap.h
        src/DeviceDriver_VirtualCheap.cpp
        src/DeviceDriver_VirtualCheap.h
        src/ServerDriver_VirtualCheap.cpp
        src/ServerDriver_VirtualCheap.h
        src/driverlog.cpp
        src/driverlog.h
        )

add_definitions(-DDRIVER_SAMPLE_EXPORTS)
add_library("driver_VirtualCheap" SHARED ${SOURCE_FILES})
