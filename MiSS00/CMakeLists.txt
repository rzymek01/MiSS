cmake_minimum_required(VERSION 3.3)
project(MiSS00)

find_package(GMP REQUIRED)
include_directories(${GOBJECT_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(SOURCE_FILES main.cpp)
add_executable(MiSS00 ${SOURCE_FILES})
target_link_libraries(MiSS00 ${GOBJECT_LIBRARIES})
