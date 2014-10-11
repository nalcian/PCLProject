cmake_minimum_required(VERSION 2.8 FATAL_ERROR)


## Macro For MACOSX
macro(ADD_FRAMEWORK fwname appname)
    find_library(FRAMEWORK_${fwname}
    NAMES ${fwname}
    PATHS ${CMAKE_OSX_SYSROOT}/System/Library
    PATH_SUFFIXES Frameworks
    NO_DEFAULT_PATH)
    if( ${FRAMEWORK_${fwname}} STREQUAL FRAMEWORK_${fwname}-NOTFOUND)
        MESSAGE(ERROR ": Framework ${fwname} not found")
    else()
        TARGET_LINK_LIBRARIES(${appname} "${FRAMEWORK_${fwname}}/${fwname}")
        MESSAGE(STATUS "Framework ${fwname} found at ${FRAMEWORK_${fwname}}")
    endif()
endmacro(ADD_FRAMEWORK)

#################
#Declare Project#
#################
project(PCLProject)

#############
#Find OpenGl#
#############
find_package(PCL 1.7 REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
#############
#Find OpenGl#
#############
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
###########
#Find GLUT#
###########
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})
#############
#Executables#
#############
add_executable(PCL_out ../src/pclTest.cpp)
add_executable(OGL_out ../src/oglTest.cpp)
#########
#Linking#
#########
target_link_libraries(PCL_out ${PCL_LIBRARIES})
target_link_libraries(OGL_out ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
###END###