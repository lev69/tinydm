if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Debug")
endif()

message(STATUS "CMAKE_BUILD_TYPE set to " ${CMAKE_BUILD_TYPE})
cmake_minimum_required(VERSION 3.1)

project(tinydmd)
set(tinydmd_VERSION_MAJOR 0)
set(tinydmd_VERSION_MINOR 1)
set(tinydmd_VERSION_PATCH 0)

if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_VERBOSE_MAKEFILE OFF)

message(STATUS "CMAKE_C_FLAGS = " ${CMAKE_C_FLAGS})
message(STATUS "CMAKE_CXX_FLAGS = " ${CMAKE_CXX_FLAGS})

### search common sources
set(TINYDM_COMMON_SOURCE_DIR
	"${CMAKE_CURRENT_SOURCE_DIR}/../common")
if(NOT EXISTS "${TINYDM_COMMON_SOURCE_DIR}/CMakeLists.txt")
	message(FATAL_ERROR "common sources not found")
endif()

add_subdirectory(${TINYDM_COMMON_SOURCE_DIR} "common")
include_directories(${CMAKE_CURRENT_BINARY_DIR}/common)
if (NOT TINYDM_COMMON_INCLUDE_DIR)
	message(FATAL_ERROR "Expected variable TINYDM_COMMON_INCLUDE_DIR is not set")
endif()

include_directories(${TINYDM_COMMON_INCLUDE_DIR})

set(CMAKE_INCLUDE_CURRENT_DIR ON)

macro(INCLUDE_SUBDIR SUBDIR)
	set(current_SUBDIR ${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIR})
	include(${SUBDIR}/${SUBDIR}.cmake)
endmacro()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/service_cmake_config.h.in
	${CMAKE_CURRENT_BINARY_DIR}/service_cmake_config.h)

set(tinydmd_SOURCES
	main.cpp
#	controller.cpp
	)

set(SHARED_SOURCES)
set(SHARED_LIBRARIES)

INCLUDE_SUBDIR(disk)
INCLUDE_SUBDIR(modules)
INCLUDE_SUBDIR(http)

set(tinydmd_SOURCES ${tinydmd_SOURCES}
	${SHARED_SOURCES}
	)

set(tinydmd_LIBRARIES
	${SHARED_LIBRARIES}
	${TINYDM_COMMON_LINK_LIBRARIES}
	)

add_executable(${PROJECT_NAME} ${tinydmd_SOURCES})
target_link_libraries(${PROJECT_NAME} ${tinydmd_LIBRARIES})
