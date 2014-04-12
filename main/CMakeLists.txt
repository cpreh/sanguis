include(
	AwlMainGenerator
)

set(
	SANGUIS_MAIN_FILES
	include/sanguis/main.hpp
	src/main.cpp
)

fcppt_utils_add_source_groups(
	"${SANGUIS_MAIN_FILES}"
)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

awl_utils_add_portable_executable(
	sanguis
	"sanguis::main"
	${SANGUIS_MAIN_FILES}
)

fcppt_utils_set_target_compiler_flags(
	sanguis
)

target_link_libraries(
	sanguis
	PRIVATE
	${sanguis_client_TARGET}
	${sanguis_core_TARGET}
	${fcppt_core_TARGET}
	${awl_TARGET}
	${sgeconfig_TARGET}
	${Boost_PROGRAM_OPTIONS_LIBRARIES}
)

install(
	TARGETS
	sanguis
	DESTINATION
	${INSTALL_BINARY_DIR}
)
