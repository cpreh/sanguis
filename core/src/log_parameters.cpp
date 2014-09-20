#include <sanguis/log_context.hpp>
#include <sanguis/log_parameters.hpp>
#include <sanguis/log_stream.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/location_fwd.hpp>
#include <fcppt/log/parameters/object.hpp>
#include <fcppt/log/parameters/with_context.hpp>


fcppt::log::parameters::object
sanguis::log_parameters(
	fcppt::log::location const &_location
)
{
	return
		fcppt::log::parameters::with_context(
			sanguis::log_context(),
			_location
		)
		.level_defaults(
			sanguis::log_stream(),
			fcppt::log::level::warning
		)
		.enabled(
			true
		);
}
