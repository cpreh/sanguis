#include <sanguis/client/log.hpp>
#include <sanguis/client/log_location.hpp>
#include <sanguis/log_parameters.hpp>
#include <sge/log/declare_lib_base.hpp>
#include <fcppt/log/parameters/object.hpp>
#include <fcppt/log/location.hpp>

SGE_LOG_DECLARE_LIB_BASE(
	sanguis::client::log,
	sanguis::log_parameters(
		sanguis::client::log_location()
	)
)
