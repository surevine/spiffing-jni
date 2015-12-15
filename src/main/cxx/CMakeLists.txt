cmake_minimum_required(VERSION 3.0)
project(spiffing_jni_cxx)
find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})
include_directories(/home/dwd/src/spiffing/include/)
include_directories(/home/dwd/libb64/include/)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES site.cc handle.h com_surevine_spiffing_Site.h label.cc spif.cc base64.cc base64.h exception.cc exception.h clearance.cc)

link_directories(/home/dwd/src/spiffing/build/)
add_library(spiffing-jni SHARED ${SOURCE_FILES})
target_link_libraries(spiffing-jni PRIVATE spiffing spiffing-asn)
