cmake_minimum_required(
	VERSION 2.6
)

project (sanguis)

include(FcpptCMakeUtils)

set (STATECHART_INCLUDE_DIR "" CACHE PATH "Include path for statechart")

if(NOT STATECHART_INCLUDE_DIR)
	message(
		FATAL_ERROR
		"Please specify the include dir of the modified statechart library, for example:
		cmake -D STATECHART_INCLUDE_DIR=foobar/statechart/include"
	)
endif()

include_directories(
	${STATECHART_INCLUDE_DIR}
)

# Find Boost

find_package(
	Boost 1.47.0 REQUIRED COMPONENTS
	chrono
	iostreams
	program_options
	system
	thread
)

add_definitions(
	-D BOOST_ASIO_SEPARATE_COMPILATION
)

include_directories(
	${Boost_INCLUDE_DIRS}
)

link_directories(
	${Boost_LIBRARY_DIRS}
)

# Find Mizuiro

find_package(
	mizuiro REQUIRED
)

add_definitions(
	${mizuiro_definitions}
)

include_directories(
	${mizuiro_INCLUDE_DIRS}
)

# Find FCPPT

find_package(
	fcppt REQUIRED
)

add_definitions(
	${fcppt_DEFINITIONS}
)

include_directories(
	${fcppt_INCLUDE_DIRS}
)

# Find Threads

find_package(
	FcpptThreads REQUIRED
)

add_definitions(
	${FcpptThreads_DEFINITIONS}
)

# Find AWL

find_package(
	awl REQUIRED
)

add_definitions(
	${awl_DEFINITIONS}
)

include_directories(
	${awl_INCLUDE_DIRS}
)

# Find SGE

find_package(
	sge REQUIRED
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

add_definitions(
	${sge_DEFINITIONS}
)

include_directories(
	${sge_INCLUDE_DIRS}
)

# Find CEGUI

find_package(
	CEGUI REQUIRED
)

include_directories(
	${CEGUI_INCLUDE_DIRS}
)

include_directories(
	${CMAKE_SOURCE_DIR}/creator/include
)

# Find ALDA

find_package(
	alda REQUIRED
)

add_definitions(
	${alda_DEFINITIONS}
)

include_directories(
	${alda_INCLUDE_DIRS}
)

include(
	SGECustomPath
)

set(
	INSTALL_MEDIA_DIR
	${INSTALL_DATA_DIR}/media
)

sge_config_add_custom_path(
	sanguis
	media
	${CMAKE_SOURCE_DIR}/media
	${INSTALL_MEDIA_DIR}
)

add_subdirectory(
	src
)

add_subdirectory(
	creator
)

install(
	DIRECTORY
	media/
	DESTINATION
	${INSTALL_MEDIA_DIR}
)
