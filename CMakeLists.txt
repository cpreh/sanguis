CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

project (sanguis)

INCLUDE(FcpptCMakeUtils)

SET (STATECHART_INCLUDE_DIR "" CACHE PATH "Include path for statechart")

IF(NOT STATECHART_INCLUDE_DIR)
	MESSAGE(
		FATAL_ERROR
		"Please specify the include dir of the modified statechart library, for example:
		cmake -D STATECHART_INCLUDE_DIR=foobar/statechart/include"
	)
ENDIF()

INCLUDE_DIRECTORIES(
	${STATECHART_INCLUDE_DIR}
)

# Find Boost

FIND_PACKAGE(
	Boost 1.47.0 REQUIRED COMPONENTS
	chrono
	iostreams
	program_options
	system
	thread
)

ADD_DEFINITIONS(-D BOOST_ASIO_SEPARATE_COMPILATION)

INCLUDE_DIRECTORIES(
	${Boost_INCLUDE_DIRS}
)

LINK_DIRECTORIES(
	${Boost_LIBRARY_DIRS}
)

# Find Mizuiro

FIND_PACKAGE(
	Mizuiro REQUIRED
)

INCLUDE_DIRECTORIES(
	${Mizuiro_INCLUDE_DIRS}
)

# Find FCPPT

FIND_PACKAGE(
	Fcppt REQUIRED
)

ADD_DEFINITIONS(
	${Fcppt_DEFINITIONS}
)

INCLUDE_DIRECTORIES(
	${Fcppt_INCLUDE_DIRS}
)

# Find Threads

find_package(
	FcpptThreads REQUIRED
)

add_definitions(
	${FcpptThreads_DEFINITIONS}
)

# Find AWL

FIND_PACKAGE(
	Awl REQUIRED
)

INCLUDE_DIRECTORIES(
	${Awl_INCLUDE_DIRS}
)

# Find SGE

FIND_PACKAGE(
	SGE REQUIRED
	COMPONENTS
	cegui
	charconv
	config
	console
	core
	font
	fontdraw
	image
	image2d
	input
	log
	parse
	projectile
	renderer
	sprite
	systems
	texture
	timer
	viewport
	window
)

ADD_DEFINITIONS(
	${SGE_DEFINITIONS}
)

INCLUDE_DIRECTORIES(
	${SGE_INCLUDE_DIRS}
)

# Find CEGUI

FIND_PACKAGE(
	CEGUI REQUIRED
)

INCLUDE_DIRECTORIES(
	${CEGUI_INCLUDE_DIRS}
)

INCLUDE_DIRECTORIES(
	${CMAKE_SOURCE_DIR}/creator/include
)

# Find ALDA

FIND_PACKAGE(
	Alda REQUIRED
)

INCLUDE_DIRECTORIES(
	${Alda_INCLUDE_DIRS}
)

INCLUDE(
	SGECustomPath
)

SET(
	INSTALL_MEDIA_DIR
	${INSTALL_DATA_DIR}/media
)

SGE_CONFIG_ADD_CUSTOM_PATH(
	sanguis
	media
	${CMAKE_SOURCE_DIR}/media
	${INSTALL_MEDIA_DIR}
)

ADD_SUBDIRECTORY(
	src
)

ADD_SUBDIRECTORY(
	creator
)

INSTALL(
	DIRECTORY
	media/
	DESTINATION
	${INSTALL_MEDIA_DIR}
)
