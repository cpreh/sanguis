#include "log.hpp"
#include "log_location.hpp"
#include "../../log_parameters.hpp"
#include <sge/log/declare_lib_base.hpp>
#include <fcppt/log/parameters/all.hpp>
#include <fcppt/log/location.hpp>

SGE_LOG_DECLARE_LIB_BASE(
	sanguis::server::weapons::log,
	sanguis::log_parameters(
		sanguis::server::weapons::log_location()
	)
)
