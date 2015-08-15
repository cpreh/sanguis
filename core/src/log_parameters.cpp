#include <sanguis/log_context.hpp>
#include <sanguis/log_parameters.hpp>
#include <sanguis/log_stream.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/location_fwd.hpp>
#include <fcppt/log/parameters.hpp>


fcppt::log::parameters
sanguis::log_parameters(
	fcppt::log::location const &_location
)
{
	return
		fcppt::log::parameters(
			sanguis::log_stream(),
			fcppt::log::level::warning
		)
		.context_location(
			sanguis::log_context(),
			_location
		)
		.enabled(
			true
		);
}
