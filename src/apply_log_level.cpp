#include <sanguis/apply_log_level.hpp>
#include <fcppt/log/activate_levels.hpp>
#include <fcppt/log/context.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/location_fwd.hpp>
#include <fcppt/log/tree_function.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


void
sanguis::apply_log_level(
	fcppt::log::location const &_location,
	fcppt::log::context &_context,
	fcppt::log::level const _level
)
{
	_context.apply(
		_location,
		fcppt::log::tree_function(
			std::bind(
				fcppt::log::activate_levels,
				std::placeholders::_1,
				_level
			)
		)
	);
}
