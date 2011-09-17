#include "log_parameters.hpp"
#include "log_context.hpp"
#include <fcppt/io/clog.hpp>
#include <fcppt/log/parameters/all.hpp>
#include <fcppt/log/parameters/with_context.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/location_fwd.hpp>

fcppt::log::parameters::all const
sanguis::log_parameters(
	fcppt::log::location const &_location
)
{
	return
		fcppt::log::parameters::with_context(
			sanguis::log_context(),
			fcppt::io::clog,
			_location
		)
		.level_defaults(
			fcppt::log::level::warning
		)
		.enabled(
			true
		);
}
