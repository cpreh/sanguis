#include <sanguis/apply_log_level.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/log/activate_levels.hpp>
#include <fcppt/log/context.hpp>
#include <fcppt/log/location_fwd.hpp>
#include <fcppt/log/tree_function.hpp>
#include <fcppt/tr1/functional.hpp>

void
sanguis::apply_log_level(
	fcppt::log::location const &_location,
	fcppt::log::context &_context,
	fcppt::log::level::type const _level
)
{
	_context.apply(
		_location,
		fcppt::log::tree_function(
			std::tr1::bind(
				fcppt::log::activate_levels,
				std::tr1::placeholders::_1,
				_level
			)
		)
	);
}
