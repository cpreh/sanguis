include(
	AwlMainGenerator
)

function(
	sanguis_add_tool
	TOOL_NAME
	TOOL_FILES
)
	set(
		SINGLE_ARGS
		"IS_GUI"
	)

	set(
		MULTI_ARGS
		"INCLUDE_DIRS"
		"LINK_LIBS"
	)

	cmake_parse_arguments(
		""
		""
		"${SINGLE_ARGS}"
		"${MULTI_ARGS}"
		${ARGN}
	)

	set(
		FULL_NAME
		sanguis_tools_${TOOL_NAME}
	)

	if(
		_IS_GUI
	)
		awl_utils_add_portable_executable(
			"${FULL_NAME}"
			"sanguis::tools::${TOOL_NAME}::main"
			${TOOL_FILES}
		)
	else()
		add_executable(
			${FULL_NAME}
			${TOOL_FILES}
		)
	endif()

	set_target_properties(
		"${FULL_NAME}"
		PROPERTIES
		FOLDER
		sanguis/tools
	)

	fcppt_utils_set_target_compiler_flags(
		${FULL_NAME}
	)

	target_include_directories(
		${FULL_NAME}
		PRIVATE
		${CMAKE_CURRENT_BINARY_DIR}
		${_INCLUDE_DIRS}
	)

	target_link_libraries(
		${FULL_NAME}
		${_LINK_LIBS}
	)

	install(
		TARGETS
		${FULL_NAME}
		DESTINATION
		${CMAKE_INSTALL_BINDIR}
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
