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

awl_utils_add_portable_executable(
	sanguis
	"sanguis::main"
	${SANGUIS_MAIN_FILES}
)

fcppt_utils_set_target_compiler_flags(
	sanguis
)

set_target_properties(
	sanguis
	PROPERTIES
	FOLDER
	sanguis
)

target_link_libraries(
	sanguis
	PRIVATE
	${sanguis_client_TARGET}
	${sanguis_core_TARGET}
	${fcppt_core_TARGET}
	${fcppt_options_TARGET}
	${awl_TARGET}
)

target_include_directories(
	sanguis
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

install(
	TARGETS
	sanguis
	DESTINATION
	${CMAKE_INSTALL_BINDIR}
)
