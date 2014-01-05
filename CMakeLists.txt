cmake_minimum_required(
	VERSION 2.6
)

project(
	sanguis
)

include(
	FcpptCMakeUtils
)

# Find Boost

find_package(
	Boost 1.47.0 REQUIRED COMPONENTS
	filesystem
	iostreams
	program_options
	system
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

option(
	ENABLE_PROJECTILE
	"Build the projectile collision backend"
	OFF
)

# Find SGE
set(
	NEEDED_SGE_COMPONENTS
	audio
	charconv
	config
	console
	core
	font
	fontdraw
	imagecolor
	image2d
	input
	log
	parse
	renderer
	rucksack
	sprite
	systems
	texture
	timer
	viewport
	window
)

if(
	ENABLE_PROJECTILE
)
	list(
		APPEND
		NEEDED_SGE_COMPONENTS
		projectile
	)
endif()

find_package(
	sge REQUIRED
	COMPONENTS
	"${NEEDED_SGE_COMPONENTS}"
)

add_definitions(
	${sge_DEFINITIONS}
)

include_directories(
	${sge_INCLUDE_DIRS}
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
	${FCPPT_UTILS_PROJECT_SOURCE_DIR}/media
	${INSTALL_MEDIA_DIR}
)

include(
	FcpptSymbol
)

function(
	sanguis_generate_symbol_header
	LIB_NAME
)
	string(
		TOUPPER
		"${LIB_NAME}"
		UPPER_NAME
	)

	fcppt_generate_symbol_header(
		"SANGUIS_STATIC_LINK"
		"sanguis${LIB_NAME}"
		"SANGUIS_${UPPER_NAME}"
		"sanguis/${LIB_NAME}"
	)
endfunction()

include_directories(
	${FCPPT_UTILS_PROJECT_BINARY_DIR}/include
)

option(
	ENABLE_SHARED
	"Build shared libraries"
	TRUE
)

option(
	ENABLE_STATIC
	"Build static libraries"
	FALSE
)

if(
	NOT ENABLE_SHARED AND NOT ENABLE_STATIC
)
	message(
		FATAL_ERROR
		"You disabled both STATIC and SHARED"
	)
endif()

if(
	NOT ENABLE_SHARED AND ENABLE_STATIC
)
	add_definitions(
		"-D SANGUIS_STATIC_LINK"
	)
endif()

macro(
	sanguis_add_library_base
	LIBNAME
	FILES
	DEPS
	VARIANT
)
	add_library(
		"${LIBNAME}"
		"${VARIANT}"
		${FILES}
	)

	target_link_libraries(
		"${LIBNAME}"
		${DEPS}
	)

	install(
		TARGETS
		"${LIBNAME}"
		DESTINATION
		"${INSTALL_LIBRARY_DIR}"
	)
endmacro()

macro(
	sanguis_add_library
	LIBNAME
	FILES
	DEPS
)
	fcppt_utils_add_source_groups(
		"${FILES}"
	)

	if(
		ENABLE_STATIC
	)
		sanguis_add_library_base(
			"${LIBNAME}_static"
			"${FILES}"
			"${DEPS}"
			"STATIC"
		)

		set(
			"${LIBNAME}_TARGET_TEMP"
			"${LIBNAME}_static"
		)
	endif()

	if(
		ENABLE_SHARED
	)
		sanguis_add_library_base(
			"${LIBNAME}"
			"${FILES}"
			"${DEPS}"
			"SHARED"
		)

		set(
			"${LIBNAME}_TARGET_TEMP"
			"${LIBNAME}"
		)
	endif()

	set(
		"${LIBNAME}_TARGET"
		"${${LIBNAME}_TARGET_TEMP}"
		CACHE
		INTERNAL
		""
	)
endmacro()

add_subdirectory(
	creator
)

add_subdirectory(
	collision
)

add_subdirectory(
	gui
)

add_subdirectory(
	src
)

install(
	DIRECTORY
	media/
	DESTINATION
	${INSTALL_MEDIA_DIR}
)
