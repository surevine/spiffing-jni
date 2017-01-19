cmake_minimum_required(VERSION 3.0)
project(spiffing_jni)
find_package(JNI REQUIRED)
find_package(Java)
include(UseJava)
include_directories(${JNI_INCLUDE_DIRS})

# Check that we can use javah
if(NOT Java_JAVAH_EXECUTABLE)
  message(FATAL_ERROR "Cannot locate javah executable. Please specify or disable Java bindings")
endif(NOT Java_JAVAH_EXECUTABLE)

# Macro to generate JNI headers
macro(javah JAVA_TARGET)
add_custom_target(javah_${JAVA_TARGET} DEPENDS ${JAVA_TARGET}
  COMMAND "${Java_JAVAH_EXECUTABLE}" -jni -classpath ./${JAVA_TARGET}.jar ${ARGN}
  #COMMAND "cmake -E touch ${CMAKE_CURRENT_LIST_FILE}"
  #WORKING_DIRECTORY "${CMAKE_JAVA_TARGET_OUTPUT_DIR}${CMAKE_FILES_DIRECTORY}/${JAVA_TARGET}.dir"
  COMMENT "Updating JNI headers for ${JAVA_TARGET}" VERBATIM
)
endmacro(javah)

macro(mvn_install MVN_TARGET MVN_FILE MVN_PACKAGING MVN_GROUP MVN_ARTIFACT MVN_VERSION)
set(MVN_TARGET_PATH ${MVN_FILE})
get_filename_component(MVN_TARGET_FILE ${MVN_TARGET_PATH} NAME)
add_custom_target(mvn_install_${MVN_TARGET}
	DEPENDS ${MVN_TARGET}
	COMMAND "mvn" install:install-file -Dfile=${MVN_TARGET_FILE} -DgroupId=${MVN_GROUP} -DartifactId=${MVN_ARTIFACT} -Dversion=${MVN_VERSION} -Dpackaging=${MVN_PACKAGING}
	COMMENT "Installing ${MVN_TARGET_FILE} ${MVN_VERSION} into Maven"
)
endmacro(mvn_install)

include_directories(${CMAKE_SOURCE_DIR}/../spiffing/include/)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES cxx/site.cc cxx/handle.h cxx/label.cc cxx/spif.cc cxx/base64.cc cxx/base64.h cxx/exception.cc cxx/exception.h cxx/clearance.cc com_surevine_spiffing_Label.h com_surevine_spiffing_Site.h)
set_property(SOURCE com_surevine_spiffing_Site.h com_surevine_spiffing_Label.h PROPERTY GENERATED TRUE)
javah(spiffing-jar
	"com.surevine.spiffing.Site"
	"com.surevine.spiffing.Label"
	"com.surevine.spiffing.Clearance"
	"com.surevine.spiffing.Spif"
)

link_directories(${CMAKE_SOURCE_DIR}/../spiffing/build/)
add_library(spiffing-jni SHARED ${SOURCE_FILES})
add_dependencies(spiffing-jni javah_spiffing-jar)
target_link_libraries(spiffing-jni PRIVATE spiffing spiffing-asn)
set(SPIFFING_FILE ${CMAKE_SHARED_LIBRARY_PREFIX}spiffing-jni${CMAKE_SHARED_LIBRARY_SUFFIX})
mvn_install(spiffing-jni ${SPIFFING_FILE} so com.surevine.spiffing spiffing-native 1.0-SNAPSHOT)

file(GLOB JAVA_SOURCE java/src/main/java/com/surevine/spiffing/*.java)
add_jar(spiffing-jar ${JAVA_SOURCE})
mvn_install(spiffing-jar spiffing-jar.jar jar com.surevine.spiffing spiffing-jni 1.0-SNAPSHOT)

add_custom_target(mvn_install DEPENDS mvn_install_spiffing-jar mvn_install_spiffing-jni)

