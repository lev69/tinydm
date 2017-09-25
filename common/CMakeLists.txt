if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Debug")
endif()

message(STATUS "CMAKE_BUILD_TYPE set to " ${CMAKE_BUILD_TYPE})
cmake_minimum_required(VERSION 3.1)

project(tinydm-common)
set(tinydm_common_VERSION_MAJOR 0)
set(tinydm_common_VERSION_MINOR 1)
set(tinydm_common_VERSION_PATCH 1)

OPTION(BUILD_STATIC "Build static library instead of shared" OFF)

if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()

message(STATUS "CMAKE_C_FLAGS = " ${CMAKE_C_FLAGS})
message(STATUS "CMAKE_CXX_FLAGS = " ${CMAKE_CXX_FLAGS})

#set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#find_package(Qt5Core REQUIRED)

macro(INCLUDE_SUBDIR SUBDIR)
	set(current_SUBDIR ${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIR})
	include(${SUBDIR}/${SUBDIR}.cmake)
endmacro()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/common_cmake_config.h.in
	${CMAKE_CURRENT_BINARY_DIR}/common_cmake_config.h)

set(tinydm_common_SOURCES
#	message_handler.cpp
    disk_info.cpp
    partition_info.cpp
	)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${INCLUDE_DIR})

set(SHARED_SOURCES)
set(SHARED_LIBRARIES)

set(tinydm_common_SOURCES ${tinydm_common_SOURCES}
	${SHARED_SOURCES}
	)

#set(tinydm_common_LIBRARIES ${SHARED_LIBRARIES})

if (${BUILD_STATIC})
	set(LIB_BUILD_TYPE STATIC)
else()
	set(LIB_BUILD_TYPE SHARED)
endif()

add_library(${PROJECT_NAME} ${LIB_BUILD_TYPE} ${tinydm_common_SOURCES})
target_link_libraries(${PROJECT_NAME} ${tinydm_common_LIBRARIES})

set(TINYDM_COMMON_INCLUDE_DIR ${INCLUDE_DIR} PARENT_SCOPE)
set(TINYDM_COMMON_LINK_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
