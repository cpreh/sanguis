set(
	SANGUIS_FILES
	include/sanguis/main.hpp
	src/main.cpp
)

fcppt_utils_append_source_dir_and_make_groups(
	"${SANGUIS_FILES}"
	SANGUIS_FILES_ABS
)

include_directories(
	${FCPPT_UTILS_PROJECT_SOURCE_DIR}/include
)

awl_utils_add_portable_executable(
	sanguis
	"sanguis::main"
	${SANGUIS_FILES_ABS}
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

if(
	WIN32
)
	target_link_libraries(
		sanguis
		PRIVATE
		WS2_32
		Mswsock
	)
endif()

install(
	TARGETS
	sanguis
	DESTINATION
	${INSTALL_BINARY_DIR}
)
