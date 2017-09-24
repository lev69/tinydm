set(SHARED_SOURCES ${SHARED_SOURCES}
	${current_SUBDIR}/disk_manager.cpp
	${current_SUBDIR}/disk_info.cpp
	${current_SUBDIR}/partition_info.cpp
	${current_SUBDIR}/disk_info_fabric.cpp
	)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
	set(SHARED_SOURCES ${SHARED_SOURCES}
		${current_SUBDIR}/parted_disk_info_fabric.cpp
		)

	set(SHARED_LIBRARIES ${SHARED_LIBRARIES}
		parted
		)
	add_definitions(-DPARTED_FABRIC_DEFINED)
endif()
