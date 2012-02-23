#include <sanguis/server/log.hpp>
#include <sanguis/server/log_location.hpp>
#include <sanguis/log_parameters.hpp>
#include <sge/log/declare_lib_base.hpp>
#include <fcppt/log/parameters/object.hpp>
#include <fcppt/log/location.hpp>

SGE_LOG_DECLARE_LIB_BASE(
	sanguis::server::log,
	sanguis::log_parameters(
		sanguis::server::log_location()
	)
)
