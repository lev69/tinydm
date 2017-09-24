find_path(CPPREST_INCLUDE cpprest/http_client.h)
find_library(CPPREST_LIB NAMES cpprest_2_9d cpprest_2_9 cpprestd cpprest)
find_package(Boost REQUIRED COMPONENTS random system thread filesystem chrono atomic date_time regex)
set(OPENSSL_ROOT_DIR "/usr/lib/openssl-1.0")
find_package(OpenSSL 1.0.0 REQUIRED)

include_directories(${CPPREST_INCLUDE})

set(SHARED_SOURCES ${SHARED_SOURCES}
	${current_SUBDIR}/rest_service.cpp
	${current_SUBDIR}/abstract_handler.cpp
	${current_SUBDIR}/get_test_handler.cpp
	${current_SUBDIR}/get_disk_info_handler.cpp
	)

set(SHARED_LIBRARIES ${SHARED_LIBRARIES}
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
