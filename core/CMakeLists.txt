set(
	SANGUIS_CORE_FILES
	include/sanguis/app_name.hpp
	include/sanguis/company_name.hpp
	include/sanguis/config_app_name.hpp
	include/sanguis/log_context.hpp
	include/sanguis/log_location.hpp
	include/sanguis/log_parameters.hpp
	src/app_name.cpp
	src/company_name.cpp
	src/config_app_name.cpp
	src/log_context.cpp
	src/log_location.cpp
	src/log_parameters.cpp
)

sanguis_generate_symbol_header_base(
	"sanguiscore"
	"SANGUIS"
	"sanguis"
)

sanguis_add_library(
	sanguiscore
	"${SANGUIS_CORE_FILES}"
	"${sgeconfig_TARGET};${fcppt_core_TARGET}"
)
