CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

project (sanguis)

SET (CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS ON)

IF(${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
	message(FATAL_ERROR "In-source builds are not permitted. Make a separate folder for building:\nmkdir build; cd build; cmake ..\nBefore that, remove the files that cmake just created:\nrm -rf CMakeCache.txt CMakeFiles")
ENDIF()

INCLUDE (FindPkgConfig)

SET (CMAKE_VERBOSE_MAKEFILE ON)

FIND_PACKAGE(Boost 1.36.0 COMPONENTS
	filesystem
	iostreams
	program_options
	system
	thread)

IF(NOT Boost_FOUND)
	MESSAGE(STATUS "Boost not found!")
ENDIF()

IF(Boost_INCLUDE_DIR)
	INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
ELSE()
	MESSAGE(STATUS "Boost headers not found. You will have to specify them in your build environment or you can use -DBOOST_ROOT= to tell cmake where your boost installation is.")
ENDIF()

IF(Boost_LIBRARY_DIRS)
	LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
ELSE()
	MESSAGE(STATUS "Boost libraries not found.")
ENDIF()

pkg_check_modules (SGE spacegameengine)

LINK_DIRECTORIES(${SGE_LIBRARY_DIRS})

IF (${CMAKE_COMPILER_IS_GNUCXX})
	ADD_DEFINITIONS("-fvisibility=hidden -ansi -pedantic-errors -Wall"
	"-Wextra -Wconversion -Wfloat-equal -Wredundant-decls"
	"-Wstrict-null-sentinel -Winit-self -Woverloaded-virtual"
	"-Wold-style-cast -Wnon-virtual-dtor -Wctor-dtor-privacy -Wsign-promo"
	"-Wstrict-aliasing=1 -Wmissing-declarations")

	ADD_DEFINITIONS(-D BOOST_FILESYSTEM_NO_DEPRECATED)
ENDIF ()



ADD_DEFINITIONS(${SGE_CFLAGS})

FILE (GLOB files 
	*.cpp
	net/*.cpp
	net/detail/*.cpp
	client/*.cpp
	client/menu/*.cpp
	client/states/*.cpp
	client_messages/*.cpp
	draw/*.cpp
	draw/factory/*.cpp
	draw/particle/*.cpp
	messages/*.cpp
	messages/serialization/*.cpp
	load/*.cpp
	load/model/*.cpp
	load/particle/*.cpp
	load/resource/*.cpp
	server/*.cpp
	server/ai/*.cpp
	server/auras/*.cpp
	server/buffs/*.cpp
	server/collision/*.cpp
	server/entities/*.cpp
	server/entities/enemies/*.cpp
	server/entities/pickups/*.cpp
	server/entities/projectiles/*.cpp
	server/message_convert/*.cpp
	server/perks/*.cpp
	server/states/*.cpp
	server/waves/*.cpp
	server/weapons/*.cpp)

ADD_EXECUTABLE(sanguis ${files})
TARGET_LINK_LIBRARIES(sanguis sgecore sgegui)

IF(NOT MSVC)
	TARGET_LINK_LIBRARIES(sanguis ${Boost_LIBRARIES} sgecore)
ENDIF()
