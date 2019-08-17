cmake_minimum_required(
	VERSION
	3.1.0
)

project(
	sanguis
)

include(
	GNUInstallDirs
)

set_property(
	GLOBAL
	PROPERTY
	USE_FOLDERS
	ON
)

option(
	ENABLE_CLIENT
	"Build the client in addition to the dedicated server"
	ON
)

option(
	ENABLE_TOOLS
	"Build tools to create content for sanguis"
	OFF
)

# Find Boost

find_package(
	Boost REQUIRED
)

# Find FCPPT

find_package(
	fcppt REQUIRED
)

include(
	FcpptCMakeUtils
)

find_package(
	Brigand
	REQUIRED
)

find_package(
	mizuiro REQUIRED
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

find_package(
	FcpptThreads REQUIRED
)

if(
	ENABLE_CLIENT
)
	list(
		APPEND
		SGE_COMPONENTS
		audio
		consolegfx
		fontdraw
		gui
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

set(
	SANGUIS_INSTALL_MEDIA_DIR
	${FCPPT_UTILS_INSTALL_DATA_DIR}/media
)

sge_config_add_custom_path(
	sanguis
	media
	${FCPPT_UTILS_PROJECT_SOURCE_DIR}/media
	${CMAKE_INSTALL_PREFIX}/${SANGUIS_INSTALL_MEDIA_DIR}
	MEDIA_PATH_INCLUDES
)

include(
	FcpptSymbol
)

function(
	sanguis_generate_symbol_header_base
	EXPORTS_NAME
	SYMBOL_NAME
	RELATIVE_PATH
)
	fcppt_generate_symbol_header(
		STATIC_LINK_FLAG
			"SANGUIS_STATIC_LINK"
		EXPORTS_NAME
			"${EXPORTS_NAME}"
		SYMBOL_NAME
			"${SYMBOL_NAME}"
		RELATIVE_PATH
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

if(
	MSVC
)
	# inheritance via dominance warning
	set(
		ADDITIONAL_COMPILE_FLAGS
		"/wd4250"
	)
endif()

function(
	sanguis_add_library_base
	LIBNAME
	VARIANT
	FILES
)
	set(
		OPTION_ARGS
		"HAS_IMPL_DIR"
	)

	set(
		MULTI_ARGS
		"DEPS"
		"TRANSITIVE_DEPS"
		"INCLUDES"
		"COMPILE_FLAGS"
		"COMPILE_DEFINITIONS"
	)

	cmake_parse_arguments(
		""
		"${OPTION_ARGS}"
		""
		"${MULTI_ARGS}"
		${ARGN}
	)

	if(
		${VARIANT}
		STREQUAL
		INTERFACE
	)
		add_library(
			${LIBNAME}
			${VARIANT}
		)
	else()
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

	endif()

	target_link_libraries(
		"${LIBNAME}"
		INTERFACE
		${_TRANSITIVE_DEPS}
	)

	set(
		PUBLIC_INCLUDES
		"${CMAKE_CURRENT_SOURCE_DIR}/include"
		${Boost_INCLUDE_DIRS}
		${BRIGAND_INCLUDE_DIRS}
	)

	target_include_directories(
		"${LIBNAME}"
		INTERFACE
		${PUBLIC_INCLUDES}
	)

	if(
		NOT
		${VARIANT}
		STREQUAL
		INTERFACE
	)
		set_target_properties(
			"${LIBNAME}"
			PROPERTIES
			FOLDER
			sanguis
		)

		target_include_directories(
			"${LIBNAME}"
			PRIVATE
			${PUBLIC_INCLUDES}
			${_INCLUDES}
		)

		if(
			_HAS_IMPL_DIR
		)
			target_include_directories(
				"${LIBNAME}"
				PRIVATE
				"${CMAKE_CURRENT_SOURCE_DIR}/impl/include"
			)
		endif()

		target_compile_definitions(
			"${LIBNAME}"
			PRIVATE
			BOOST_ALL_NO_LIB
			${_COMPILE_DEFINITIONS}
		)

		fcppt_utils_set_target_compiler_flags(
			"${LIBNAME}"
			ADDITIONAL_FLAGS
			${_COMPILE_FLAGS}
			${ADDITIONAL_COMPILE_FLAGS}
		)

		install(
			TARGETS
			"${LIBNAME}"
			DESTINATION
			"${CMAKE_INSTALL_LIBDIR}"
		)
	endif()
endfunction()

function(
	sanguis_add_library
	LIBNAME
	FILES
)
	set(
		OPTION_ARGS
		"HAS_IMPL_DIR"
	)

	set(
		MULTI_ARGS
		"DEPS"
		"TRANSITIVE_DEPS"
		"INCLUDES"
		"COMPILE_FLAGS"
		"COMPILE_DEFINITIONS"
		"COMPILE_DEFINITIONS_SHARED_PUBLIC"
		"COMPILE_DEFINITIONS_SHARED_PRIVATE"
		"COMPILE_DEFINITIONS_STATIC_PUBLIC"
	)

	cmake_parse_arguments(
		""
		"${OPTION_ARGS}"
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

	sanguis_add_library_base(
		${FULL_NAME}_interface
		"INTERFACE"
		"${FILES}"
		TRANSITIVE_DEPS
			${_TRANSITIVE_DEPS}
	)

	target_compile_definitions(
		${FULL_NAME}_interface
		INTERFACE
		${_COMPILE_DEFINITIONS_SHARED_PUBLIC}
	)

	if(
		_HAS_IMPL_DIR
	)
		set(
			HAS_IMPL_DIR
			HAS_IMPL_DIR
		)
	endif()

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
			${HAS_IMPL_DIR}
			DEPS
				${_DEPS}
			TRANSITIVE_DEPS
				${_TRANSITIVE_DEPS}
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
			${HAS_IMPL_DIR}
			DEPS
				${_DEPS}
			TRANSITIVE_DEPS
				${_TRANSITIVE_DEPS}
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

function(
	sanguis_add_executable
	EXENAME
	FILES
)
	set(
		SINGLE_ARGS
		"FOLDER"
		"MAIN_NAMESPACE"
	)

	set(
		MULTI_ARGS
		"DEPS"
		"COMPILE_OPTIONS"
		"INCLUDE_DIRS"
		"COMPILE_DEFINITIONS"
	)

	cmake_parse_arguments(
		""
		""
		"${SINGLE_ARGS}"
		"${MULTI_ARGS}"
		${ARGN}
	)

	fcppt_utils_add_source_groups(
		"${FILES}"
	)

	if(
		"${_MAIN_NAMESPACE}"
		STREQUAL
		""
	)
		add_executable(
			${EXENAME}
			${FILES}
		)
	else()
		awl_utils_add_portable_executable(
			${EXENAME}
			${_MAIN_NAMESPACE}
			${FILES}
		)
	endif()

	fcppt_utils_set_target_compiler_flags(
		${EXENAME}
		ADDITIONAL_FLAGS
		${ADDITIONAL_COMPILE_FLAGS}
	)

	if(
		"${_FOLDER}"
		STREQUAL
		""
	)
		set(
			FOLDER
			sanguis
		)
	else()
		set(
			FOLDER
			${_FOLDER}
		)
	endif()

	set_target_properties(
		${EXENAME}
		PROPERTIES
		FOLDER
		${FOLDER}
	)

	target_include_directories(
		${EXENAME}
		PRIVATE
		${_INCLUDE_DIRS}
		${BRIGAND_INCLUDE_DIRS}
		${Boost_INCLUDE_DIRS}
	)

	target_compile_options(
		${EXENAME}
		PRIVATE
		${_COMPILE_OPTIONS}
	)

	target_compile_definitions(
		${EXENAME}
		PRIVATE
		${_COMPILE_DEFINITIONS}
		BOOST_ALL_NO_LIB
	)

	target_link_libraries(
		${EXENAME}
		PRIVATE
		${_DEPS}
	)

	install(
		TARGETS
		${EXENAME}
		DESTINATION
		${CMAKE_INSTALL_BINDIR}
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
		tiles
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
	${SANGUIS_INSTALL_MEDIA_DIR}
)
