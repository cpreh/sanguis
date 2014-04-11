include(
	AwlMainGenerator
)

function(
	sanguis_add_tool
	TOOL_NAME
	TOOL_FILES
	INCLUDE_DIRS
	LINK_LIBS
	IS_GUI
)
	set(
		FULL_NAME
		sanguis_tools_${TOOL_NAME}
	)

	if(
		IS_GUI
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

	fcppt_utils_set_target_compiler_flags(
		${FULL_NAME}
	)

	target_include_directories(
		${FULL_NAME}
		PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/include
		${CMAKE_CURRENT_BINARY_DIR}
		${INCLUDE_DIRS}
	)

	target_link_libraries(
		${FULL_NAME}
		${LINK_LIBS}
	)

	install(
		TARGETS
		${FULL_NAME}
		DESTINATION
		${INSTALL_BINARY_DIR}
	)
endfunction()

add_subdirectory(
	animations
)

add_subdirectory(
	check_json
)

add_subdirectory(
	libmergeimage
)

add_subdirectory(
	mergeimage
)
