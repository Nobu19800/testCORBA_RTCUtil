cmake_minimum_required(VERSION 3.1)

set(target CORBA_RTCUtil_test)
project(${target} CXX)

find_package(OpenRTM REQUIRED)

add_definitions(${OPENRTM_CFLAGS})
link_directories(${OPENRTM_LIBRARY_DIRS})

add_executable(${target} ${target}.cpp)
target_link_libraries(${target} ${OPENRTM_LIBRARIES})
target_include_directories(${target} SYSTEM PRIVATE ${OPENRTM_INCLUDE_DIRS})
