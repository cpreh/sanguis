#include <sanguis/log.hpp>
#include <sanguis/log_location.hpp>
#include <sanguis/log_parameters.hpp>
#include <fcppt/log/define_object.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/log/parameters/object.hpp>


FCPPT_LOG_DEFINE_OBJECT(
	sanguis::log,
	sanguis::log_parameters(
		sanguis::log_location()
	)
)
