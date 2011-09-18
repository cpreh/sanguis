#include <sanguis/log.hpp>
#include <sanguis/log_location.hpp>
#include <sanguis/log_parameters.hpp>
#include <sge/log/declare_lib_base.hpp>
#include <fcppt/log/parameters/all.hpp>
#include <fcppt/log/location.hpp>

SGE_LOG_DECLARE_LIB_BASE(
	sanguis::log,
	sanguis::log_parameters(
		sanguis::log_location()
	)
)
