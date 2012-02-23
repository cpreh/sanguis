#include <sanguis/server/weapons/log.hpp>
#include <sanguis/server/weapons/log_location.hpp>
#include <sanguis/log_parameters.hpp>
#include <sge/log/declare_lib_base.hpp>
#include <fcppt/log/parameters/object.hpp>
#include <fcppt/log/location.hpp>

SGE_LOG_DECLARE_LIB_BASE(
	sanguis::server::weapons::log,
	sanguis::log_parameters(
		sanguis::server::weapons::log_location()
	)
)
