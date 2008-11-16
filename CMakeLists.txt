CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

project (sanguis)

IF(${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
	message(FATAL_ERROR "In-source builds are not permitted. Make a separate folder for building:\nmkdir build; cd build; cmake ..\nBefore that, remove the files that cmake just created:\nrm -rf CMakeCache.txt CMakeFiles")
ENDIF(${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR})

INCLUDE (FindPkgConfig)

SET (CMAKE_VERBOSE_MAKEFILE ON)
SET (CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS ON)

pkg_check_modules (SGE spacegameengine)

ADD_DEFINITIONS(${SGE_CFLAGS})
LINK_DIRECTORIES(${SGE_LIBRARY_DIRS})

FIND_PACKAGE(Boost 1.36.0 COMPONENTS
	filesystem
	serialization
	thread,
	program_options)

IF (${CMAKE_COMPILER_IS_GNUCXX})
	ADD_DEFINITIONS("-fvisibility=hidden -ansi -pedantic-errors -Wall -Wextra -Wconversion -Wfloat-equal -Wredundant-decls -Wstrict-null-sentinel -Winit-self -Woverloaded-virtual -Wold-style-cast")
ENDIF ()

FILE (GLOB files 
	*.cpp
	net/*.cpp
	client/*.cpp
	client_messages/*.cpp
	draw/*.cpp
	draw/factory/*.cpp
	messages/*.cpp
	load/*.cpp
	load/model/*.cpp
	load/resource/*.cpp
	server/*.cpp
	server/ai/*.cpp
	server/auras/*.cpp
	server/entities/*.cpp
	server/entities/enemies/*.cpp
	server/entities/pickups/*.cpp
	server/entities/projectiles/*.cpp
	server/perks/*.cpp
	server/states/*.cpp
	server/waves/*.cpp
	server/weapons/*.cpp)

ADD_EXECUTABLE(sanguis ${files})
TARGET_LINK_LIBRARIES(sanguis sgecore)

IF(NOT MSVC)
	TARGET_LINK_LIBRARIES(sanguis boost_serialization boost_thread
		boost_program_options sgecore)
ENDIF()
