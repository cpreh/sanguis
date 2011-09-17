#include "log.hpp"
#include "log_location.hpp"
#include "../../log_parameters.hpp"
#include <sge/log/declare_lib_base.hpp>
#include <fcppt/log/parameters/all.hpp>
#include <fcppt/log/location.hpp>

SGE_LOG_DECLARE_LIB_BASE(
	sanguis::client::draw2d::log,
	sanguis::log_parameters(
		sanguis::client::draw2d::log_location()
	)
)
