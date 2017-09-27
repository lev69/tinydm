if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Debug")
endif()

message(STATUS "CMAKE_BUILD_TYPE set to " ${CMAKE_BUILD_TYPE})
cmake_minimum_required(VERSION 3.1)

project(tinydm-gui)
set(tinydm_gui_VERSION_MAJOR 0)
set(tinydm_gui_VERSION_MINOR 1)
set(tinydm_gui_VERSION_PATCH 0)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_VERBOSE_MAKEFILE OFF)

## search common sources
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

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/client_cmake_config.h.in
	${CMAKE_CURRENT_BINARY_DIR}/client_cmake_config.h)

set(CMAKE_AUTOMOC ON)
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

### include cpprestsdk
find_path(CPPREST_INCLUDE cpprest/http_client.h)
find_library(CPPREST_LIB NAMES cpprest_2_9d cpprest_2_9 cpprestd cpprest)
find_package(Boost REQUIRED COMPONENTS random system thread filesystem chrono atomic date_time regex)
set(OPENSSL_ROOT_DIR "/usr/lib/openssl-1.0")
find_package(OpenSSL 1.0.0 REQUIRED)

include_directories(${CPPREST_INCLUDE})

set(tinydm_gui_SOURCES
	main.cpp
	rest_client.cpp
	json_module.cpp
	message_handler.cpp
	settings_dialog.cpp
	controller.cpp
	main_window.cpp
	rest_controller.cpp
	disk_item_model.cpp
	)

set(SHARED_SOURCES)
set(SHARED_LIBRARIES)

set(tinydm_gui_SOURCES ${tinydm_gui_SOURCES}
	${SHARED_SOURCES}
	)

set(tinydm_gui_LIBRARIES
	${SHARED_LIBRARIES}
	${TINYDM_COMMON_LINK_LIBRARIES}
	Qt5::Core
	Qt5::Widgets
	${CPPREST_LIB}
	Boost::boost
	Boost::random
	Boost::system
	Boost::thread
	Boost::filesystem
	Boost::chrono
	Boost::atomic
	Boost::date_time
	Boost::regex
	OpenSSL::SSL
	)

add_executable(${PROJECT_NAME} ${tinydm_gui_SOURCES})
target_link_libraries(${PROJECT_NAME} ${tinydm_gui_LIBRARIES})
