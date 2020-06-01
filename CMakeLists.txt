cmake_minimum_required(VERSION 3.3)
project(VirtualCheap C CXX)

include_directories(openvr/headers/)

set(SOURCE_FILES
    src/main.cpp

    src/virtualcheap/logger.cpp
    src/virtualcheap/logger.h
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_SHARED_LIBRARY_PREFIX "")

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    add_library(driver_virtualcheap_64 SHARED ${SOURCE_FILES})

    set_target_properties(driver_virtualcheap_64 PROPERTIES
             LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/VirtualCheap/bin/linux64/
             OUTPUT_NAME "driver_virtualcheap"
    )
endif()

add_library(driver_virtualcheap_32 SHARED ${SOURCE_FILES})

set_target_properties(driver_virtualcheap_32 PROPERTIES
         LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/VirtualCheap/bin/linux32/
         OUTPUT_NAME "driver_virtualcheap"
         COMPILE_FLAGS "-m32"
         LINK_FLAGS "-m32"
)

add_custom_command(TARGET driver_virtualcheap_32 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources/
        ${CMAKE_CURRENT_BINARY_DIR}/VirtualCheap/
)
