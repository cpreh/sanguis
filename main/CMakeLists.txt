include(
	AwlMainGenerator
)

set(
	SANGUIS_MAIN_FILES
	include/sanguis/main.hpp
	src/main.cpp
)

sanguis_add_executable(
	sanguis
	"${SANGUIS_MAIN_FILES}"
	MAIN_NAMESPACE
		"sanguis::main"
	DEPS
		${sanguis_client_TARGET}
		${sanguis_core_TARGET}
		${fcppt_core_TARGET}
		${fcppt_options_TARGET}
		${awl_TARGET}
	INCLUDE_DIRS
		${CMAKE_CURRENT_SOURCE_DIR}/include
)
