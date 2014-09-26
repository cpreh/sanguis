#ifndef SANGUIS_SERVER_PERKS_CHANGE_SIMPLE_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_CHANGE_SIMPLE_HPP_INCLUDED

#include <sanguis/server/entities/with_perks_fwd.hpp>
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
	typename Class,
	typename ChangeFunction,
	typename ElemFunction
>
void
change_simple(
	ChangeFunction const &_change_function,
	sanguis::server::entities::with_perks &_entity,
	ElemFunction const &_elem_function,
	sanguis::server::perks::change_factor const _factor,
	sanguis::server::perks::level_diff const _diff
)
{
	_change_function(
		_elem_function(
			dynamic_cast<
				Class &
			>(
				_entity
			)
		),
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
