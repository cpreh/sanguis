#include <sanguis/log_parameters.hpp>
#include <sanguis/server/weapons/log.hpp>
#include <sanguis/server/weapons/log_location.hpp>
#include <fcppt/log/define_object.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/log/parameters/object.hpp>


FCPPT_LOG_DEFINE_OBJECT(
	sanguis::server::weapons::log,
	sanguis::log_parameters(
		sanguis::server::weapons::log_location()
	)
)
