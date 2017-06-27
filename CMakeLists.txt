cmake_minimum_required(VERSION 3.3)
project(VirtualCheap C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_SHARED_LIBRARY_PREFIX "")

include_directories(openvr/headers/)

set(SOURCE_FILES
        src/driver_VirtualCheap.cpp
        src/WatchdogDriver_VirtualCheap.cpp
        src/WatchdogDriver_VirtualCheap.h
        src/DeviceDriver_VirtualCheap.cpp
        src/DeviceDriver_VirtualCheap.h
        src/ServerDriver_VirtualCheap.cpp
        src/ServerDriver_VirtualCheap.h
        src/driverlog.cpp
        src/driverlog.h
        )

file(MAKE_DIRECTORY VirtualCheap/bin/linux64/)

add_library("driver_VirtualCheap" SHARED ${SOURCE_FILES})

set_target_properties(driver_VirtualCheap PROPERTIES
         LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/VirtualCheap/bin/linux64/)

add_custom_command(TARGET driver_VirtualCheap POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/resources/
                ${CMAKE_CURRENT_BINARY_DIR}/VirtualCheap/resources/)
add_custom_command(TARGET driver_VirtualCheap POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/driver.vrdrivermanifest
                ${CMAKE_CURRENT_BINARY_DIR}/VirtualCheap/driver.vrdrivermanifest)
