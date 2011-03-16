#ifndef SANGUIS_SERVER_PERKS_CHANGE_SIMPLE_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_CHANGE_SIMPLE_HPP_INCLUDED

#include "level_diff.hpp"
#include "../entities/base_fwd.hpp"
#include "../entities/property/value.hpp"

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
	entities::base &_entity,
	ElemFunction const &_elem_function,
	entities::property::value const _factor,
	level_diff const _diff
)
{
	_change_function(
		(
			dynamic_cast<
				Class &
			>(
				_entity
			)
			.*_elem_function
		)(),
		_factor
		*
		static_cast<
			entities::property::value
		>(
			_diff
		)
	);
}

}
}
}

#endif
