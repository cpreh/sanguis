#ifndef SANGUIS_SERVER_PERKS_CHANGE_SIMPLE_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_CHANGE_SIMPLE_HPP_INCLUDED

#include <sanguis/server/entities/property/base_fwd.hpp>
#include <sanguis/server/entities/property/value.hpp>
#include <sanguis/server/perks/change_factor.hpp>
#include <sanguis/server/perks/level_diff.hpp>
#include <fcppt/cast/int_to_float.hpp>


namespace sanguis
{
namespace server
{
namespace perks
{

template<
	typename ChangeFunction
>
void
change_simple(
	ChangeFunction const &_change_function,
	sanguis::server::entities::property::base &_property,
	sanguis::server::perks::change_factor const _factor,
	sanguis::server::perks::level_diff const _diff
)
{
	_change_function(
		_property,
		_factor.get()
		*
		fcppt::cast::int_to_float<
			sanguis::server::entities::property::value
		>(
			_diff.get()
		)
	);
}

}
}
}

#endif
