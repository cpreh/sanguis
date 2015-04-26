#include <sanguis/log_parameters.hpp>
#include <sanguis/server/log.hpp>
#include <sanguis/server/log_location.hpp>
#include <fcppt/log/define_object.hpp>
#include <fcppt/log/location.hpp>


FCPPT_LOG_DEFINE_OBJECT(
	sanguis::server::log,
	sanguis::log_parameters(
		sanguis::server::log_location()
	)
)
