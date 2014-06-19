#ifndef SANGUIS_SERVER_DAMAGE_BASIC_MAKE_ARRAY_HPP_INCLUDED
#define SANGUIS_SERVER_DAMAGE_BASIC_MAKE_ARRAY_HPP_INCLUDED

#include <sanguis/server/damage/basic_array.hpp>
#include <sanguis/server/damage/basic_meta_decl.hpp>
#include <sanguis/server/damage/basic_meta_list.hpp>
#include <fcppt/algorithm/array_init.hpp>


namespace sanguis
{
namespace server
{
namespace damage
{

template<
	typename Unit
>
sanguis::server::damage::basic_array<
	Unit
>
basic_make_array(
	sanguis::server::damage::basic_meta_list<
		Unit
	> const &_inits
)
{
	typedef
	sanguis::server::damage::basic_array<
		Unit
	>
	result_type;

	result_type result{
		fcppt::algorithm::array_init<
			typename
			result_type::internal
		>(
			Unit(
				0.f
			)
		)
	};

	for(
		auto const &element
		:
		_inits
	)
		result[
			element.type()
		] =
			element.value();

	return
		result;
}

}
}
}

#endif
