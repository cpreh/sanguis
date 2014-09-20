cmake_minimum_required(
	VERSION
	2.8.12
)

project(
	sanguis
)

include(
	FcpptCMakeUtils
)

option(
	ENABLE_CLIENT
	"Build the client in addition to the dedicated server"
	ON
)

option(
	ENABLE_PROJECTILE
	"Build the projectile collision backend"
	OFF
)

option(
	ENABLE_TOOLS
	"Build tools to create content for sanguis"
	OFF
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

# Find FCPPT

find_package(
	fcppt REQUIRED
)

set(
	SGE_COMPONENTS
	charconv
	config
	console
	font
	parse
	parsejson
	timer
)

if(
	ENABLE_CLIENT
)
	# Find Threads

	find_package(
		FcpptThreads REQUIRED
	)

	list(
		APPEND
		SGE_COMPONENTS
		audio
		consolegfx
		fontdraw
		imagecolor
		image2d
		input
		log
		parseini
		renderer
		rucksack
		rucksackviewport
		sprite
		systems
		texture
		viewport
		window
	)
endif()

if(
	ENABLE_CLIENT
	OR
	ENABLE_TOOLS
)
	find_package(
		awl REQUIRED
	)
endif()

if(
	ENABLE_TOOLS
)
	list(
		APPEND
		SGE_COMPONENTS
		image2d
	)
endif()

if(
	ENABLE_PROJECTILE
)
	list(
		APPEND
		SGE_COMPONENTS
		projectile
	)
endif()

find_package(
	sge REQUIRED
	COMPONENTS
	"${SGE_COMPONENTS}"
)

# Find ALDA

find_package(
	alda REQUIRED
)

include(
	SGECustomPath
)

fcppt_utils_install_data_dir(
	INSTALL_DATA_DIR
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
	sanguis_generate_symbol_header_base
	EXPORT_NAME
	SYMBOL_NAME
	RELATIVE_PATH
)
	fcppt_generate_symbol_header(
		"SANGUIS_STATIC_LINK"
		"${EXPORT_NAME}"
		"${SYMBOL_NAME}"
		"${RELATIVE_PATH}"
	)
endfunction()

function(
	sanguis_generate_symbol_header
	LIB_NAME
)
	string(
		TOUPPER
		"${LIB_NAME}"
		UPPER_NAME
	)

	string(
		REPLACE
		"_"
		"/"
		LIB_PATH
		"${LIB_NAME}"
	)

	sanguis_generate_symbol_header_base(
		"sanguis_${LIB_NAME}"
		"SANGUIS_${UPPER_NAME}"
		"sanguis/${LIB_PATH}"
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

include(
	CMakeParseArguments
)

function(
	sanguis_add_library_base
	LIBNAME
	VARIANT
	FILES
)
	set(
		MULTI_ARGS
		"DEPS"
		"INCLUDES"
		"COMPILE_FLAGS"
		"COMPILE_DEFINITIONS"
	)

	cmake_parse_arguments(
		""
		""
		""
		"${MULTI_ARGS}"
		${ARGN}
	)

	add_library(
		"${LIBNAME}"
		"${VARIANT}"
		${FILES}
	)

	target_link_libraries(
		"${LIBNAME}"
		PRIVATE
		${_DEPS}
	)

	target_compile_definitions(
		"${LIBNAME}"
		PRIVATE
		${_COMPILE_DEFINITIONS}
	)

	target_include_directories(
		"${LIBNAME}"
		PUBLIC
		"${CMAKE_CURRENT_SOURCE_DIR}/include"
		PRIVATE
		${_INCLUDES}
	)

	fcppt_utils_set_target_compiler_flags(
		"${LIBNAME}"
		ADDITIONAL_FLAGS
		${_COMPILE_FLAGS}
	)

	install(
		TARGETS
		"${LIBNAME}"
		DESTINATION
		"${INSTALL_LIBRARY_DIR}"
	)
endfunction()

function(
	sanguis_add_library
	LIBNAME
	FILES
)
	set(
		MULTI_ARGS
		"DEPS"
		"INCLUDES"
		"COMPILE_FLAGS"
		"COMPILE_DEFINITIONS"
		"COMPILE_DEFINITIONS_SHARED_PUBLIC"
		"COMPILE_DEFINITIONS_SHARED_PRIVATE"
		"COMPILE_DEFINITIONS_STATIC_PUBLIC"
	)

	cmake_parse_arguments(
		""
		""
		""
		"${MULTI_ARGS}"
		${ARGN}
	)

	set(
		FULL_NAME
		sanguis_${LIBNAME}
	)

	sanguis_generate_symbol_header(
		${LIBNAME}
	)

	fcppt_utils_add_source_groups(
		"${FILES}"
	)

	if(
		ENABLE_STATIC
	)
		set(
			FULL_NAME_STATIC
			"${FULL_NAME}_static"
		)

		sanguis_add_library_base(
			"${FULL_NAME_STATIC}"
			"STATIC"
			"${FILES}"
			DEPS
				${_DEPS}
			COMPILE_DEFINITIONS
				${_COMPILE_DEFINITIONS}
			COMPILE_FLAGS
				${_COMPILE_FLAGS}
			INCLUDES
				${_INCLUDES}
		)

		set(
			"${FULL_NAME}_TARGET_TEMP"
			"${FULL_NAME_STATIC}"
		)

		target_compile_definitions(
			"${FULL_NAME_STATIC}"
			PUBLIC
			"SANGUIS_STATIC_LINK"
			${_COMPILE_DEFINITIONS_STATIC_PUBLIC}
		)
	endif()

	if(
		ENABLE_SHARED
	)
		sanguis_add_library_base(
			"${FULL_NAME}"
			"SHARED"
			"${FILES}"
			DEPS
				${_DEPS}
			COMPILE_DEFINITIONS
				${_COMPILE_DEFINITIONS}
			COMPILE_FLAGS
				${_COMPILE_FLAGS}
			INCLUDES
				${_INCLUDES}
		)

		target_compile_definitions(
			"${FULL_NAME}"
			PUBLIC
			${_COMPILE_DEFINITIONS_SHARED_PUBLIC}
			PRIVATE
			${_COMPILE_DEFINITIONS_SHARED_PRIVATE}
		)

		set(
			"${FULL_NAME}_TARGET_TEMP"
			"${FULL_NAME}"
		)
	endif()

	set(
		"${FULL_NAME}_TARGET"
		"${${FULL_NAME}_TARGET_TEMP}"
		CACHE
		INTERNAL
		""
	)
endfunction()

if(
	WIN32
)
	set(
		ASIO_LIBS
		WS2_32
	)
endif()

add_subdirectory(
	core
)

add_subdirectory(
	creator
)

add_subdirectory(
	collision
)

add_subdirectory(
	model
)

add_subdirectory(
	common
)

add_subdirectory(
	server
)

if(
	ENABLE_CLIENT
)
	add_subdirectory(
		gui
	)

	add_subdirectory(
		client
	)

	add_subdirectory(
		main
	)
endif()

if(
	ENABLE_TOOLS
)
	add_subdirectory(
		tools
	)
endif()

install(
	DIRECTORY
	media/
	DESTINATION
	${INSTALL_MEDIA_DIR}
)
