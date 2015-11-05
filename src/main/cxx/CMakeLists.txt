cmake_minimum_required(VERSION 3.3)
project(spiffing_jni_cxx)
find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})
include_directories(/home/dwd/src/spiffing/include/)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES site.cpp handle.h com_surevine_spiffing_Site.h)

add_library(spiffing-jni SHARED ${SOURCE_FILES})