include(
	AwlMainGenerator
)

function(
	sanguis_add_tool
	TOOL_NAME
	TOOL_FILES
)
	set(
		OPTION_ARGS
		"IS_GUI"
	)

	set(
		MULTI_ARGS
		"COMPILE_OPTIONS"
		"INCLUDE_DIRS"
		"LINK_LIBS"
		"SYSTEM_INCLUDE_DIRS"
	)

	cmake_parse_arguments(
		""
		"${OPTION_ARGS}"
		""
		"${MULTI_ARGS}"
		${ARGN}
	)

	if(
		_IS_GUI
	)
		set(
			MAIN_NAMESPACE
			MAIN_NAMESPACE
		)

		set(
			MAIN_NAMESPACE_ARG
			"sanguis::tools::${TOOL_NAME}::main"
		)
	endif()

	sanguis_add_executable(
		sanguis_tools_${TOOL_NAME}
		"${TOOL_FILES}"
		${MAIN_NAMESPACE}
			${MAIN_NAMESPACE_ARG}
		DEPS
			${_LINK_LIBS}
		COMPILE_OPTIONS
			${_COMPILE_OPTIONS}
		INCLUDE_DIRS
			${_INCLUDE_DIRS}
		SYSTEM_INCLUDE_DIRS
			${_SYSTEM_INCLUDE_DIRS}
		FOLDER
			sanguis/tools
	)
endfunction()

add_subdirectory(
	check_json
)

add_subdirectory(
	libmergeimage
)

add_subdirectory(
	mergeimage
)

add_subdirectory(
	animations
)

if(
	ENABLE_CLIENT
)
	add_subdirectory(
		drawlevel
	)
endif()
