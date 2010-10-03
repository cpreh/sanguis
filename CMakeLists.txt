CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

project (sanguis)

SET (CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS ON)

SET (CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)

IF(${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
	MESSAGE(
		FATAL_ERROR
		"In-source builds are not permitted. "
		"Make a separate folder for building:\n"
		"mkdir build; cd build; cmake ..\n"
		"Before that, remove the files that cmake"
		"just created:\nrm -rf CMakeCache.txt CMakeFiles"
	)
ENDIF()

# Find Boost

SET (Boost_ADDITIONAL_VERSIONS "1.41" "1.41.0" "1.42" "1.42.0" "1.43" "1.43.0" "1.44" "1.44.0")

IF(MSVC)
	SET(Boost_USE_STATIC_LIBS ON)
ENDIF()

IF(NOT STATECHART_INCLUDE_DIR)
	MESSAGE(
		FATAL_ERROR
		"Please specify the include dir of the modified statechart library, for example:
		cmake -D STATECHART_INCLUDE_DIR=foobar/statechart/include"
	)
ENDIF()

INCLUDE_DIRECTORIES(${STATECHART_INCLUDE_DIR})

FIND_PACKAGE(
	Boost 1.41.0 REQUIRED COMPONENTS
	iostreams
	program_options
	system
	thread
)

INCLUDE_DIRECTORIES(SYSTEM ${Boost_INCLUDE_DIR})

LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

# Find Mizuiro

FIND_PACKAGE(
	Mizuiro REQUIRED
)

INCLUDE_DIRECTORIES(${MIZUIRO_INCLUDE_DIRS})

# Find FCPPT

FIND_PACKAGE(
	Fcppt REQUIRED
)

INCLUDE_DIRECTORIES(${FCPPT_INCLUDE_DIRS})

LINK_DIRECTORIES(${FCPPT_LIBRARY_DIRS})

# Find SGE

FIND_PACKAGE(
	SGE REQUIRED
)

INCLUDE_DIRECTORIES(${SGE_INCLUDE_DIRS})

IF (${CMAKE_COMPILER_IS_GNUCXX})
	ADD_DEFINITIONS("
		-fvisibility=hidden -ansi -pedantic-errors -Wall"
		"-Wextra -Wconversion -Wfloat-equal -Wredundant-decls"
		"-Wstrict-null-sentinel -Winit-self -Woverloaded-virtual"
		"-Wold-style-cast -Wnon-virtual-dtor -Wctor-dtor-privacy -Wsign-promo"
		"-Wstrict-aliasing=1 -Wmissing-declarations -Wno-long-long"
	)
	# we don't use long long but boost does :(

	ADD_DEFINITIONS(-D BOOST_FILESYSTEM_NO_DEPRECATED)
ELSEIF (MSVC)
	ADD_DEFINITIONS ("/W4 /wd4996 /EHa /D_BIND_TO_CURRENT_VCLIBS_VERSION=1")
ENDIF ()

ADD_DEFINITIONS(${SGE_CFLAGS})

SET(
	media_path
	${CMAKE_INSTALL_PREFIX}/share/games/sanguis
)

set_source_files_properties(
	media_path.cpp
	PROPERTIES
	COMPILE_FLAGS
	-DMEDIA_PATH="\\\"${media_path}\\\""
)

FILE (GLOB basefiles *.cpp)

FILE (
	GLOB_RECURSE collectionsfiles
	args/*.cpp
	net/*.cpp
	client/*.cpp
	client_messages/*.cpp
	draw/*.cpp
	messages/*.cpp
	load/*.cpp
	server/*.cpp
)

set_source_files_properties(
	media_path.cpp
	PROPERTIES
	COMPILE_FLAGS
	-DMEDIA_PATH="\\\"${CMAKE_INSTALL_PREFIX}/share/games/sanguis/media\\\""
)

ADD_EXECUTABLE(
	sanguis
	${basefiles}
	${collectionsfiles}
)

TARGET_LINK_LIBRARIES(
	sanguis
	${FCPPT_LIBRARIES}
	${SGE_CORE_LIBRARY}
	${SGE_GUI_LIBRARY}
)

IF(NOT MSVC)
	TARGET_LINK_LIBRARIES(sanguis ${Boost_LIBRARIES})
ENDIF()

INSTALL (DIRECTORY media/ DESTINATION share/games/sanguis/media/)

INSTALL (TARGETS sanguis DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/)
