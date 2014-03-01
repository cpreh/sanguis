set(
	SANGUIS_TOOLS_CHECK_JSON_FILES
	src/main.cpp
)

add_executable(
	sanguis_tools_check_json
	${SANGUIS_TOOLS_CHECK_JSON_FILES}
)

fcppt_utils_set_target_compiler_flags(
	sanguis_tools_check_json
)

target_link_libraries(
	sanguis_tools_check_json
	PRIVATE
	${sanguismodel_TARGET}
	${fcppt_core_TARGET}
	${Boost_FILESYSTEM_LIBRARIES}
)

install(
	TARGETS
	sanguis_tools_check_json
	DESTINATION
	${INSTALL_BINARY_DIR}
)
