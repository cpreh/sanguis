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
	ChangeFunction const &change_function_,
	entities::base &entity_,
	ElemFunction const &elem_function_,
	entities::property::value const factor_,
	level_diff const diff_
)
{
	change_function_(
		(
			dynamic_cast<
				Class &
			>(
				entity_
			)
			.*elem_function_
		)(),
		factor_
		*
		static_cast<
			entities::property::value
		>(
			diff_
		)
	);
}

}
}
}

#endif
