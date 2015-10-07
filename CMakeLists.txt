cmake_minimum_required(VERSION 3.3)
project(MiSS00)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#find_package(GMP REQUIRED)
#include_directories(${GOBJECT_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lgmpxx -lgmp")

set(SOURCE_FILES main.cpp)
add_executable(MiSS00 ${SOURCE_FILES})
#target_link_libraries(ExecutableName ${GOBJECT_LIBRARIES})