#include <sanguis/log_parameters.hpp>
#include <sanguis/net/log.hpp>
#include <sanguis/net/log_location.hpp>
#include <fcppt/log/define_object.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/log/parameters/object.hpp>


FCPPT_LOG_DEFINE_OBJECT(
	sanguis::net::log,
	sanguis::log_parameters(
		sanguis::net::log_location()
	)
)
