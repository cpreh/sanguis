#ifndef SANGUIS_SERVER_DAMAGE_BASIC_MAKE_ARRAY_HPP_INCLUDED
#define SANGUIS_SERVER_DAMAGE_BASIC_MAKE_ARRAY_HPP_INCLUDED

#include <sanguis/server/damage/basic_array.hpp>
#include <sanguis/server/damage/basic_meta_decl.hpp>
#include <sanguis/server/damage/basic_meta_list.hpp>
#include <fcppt/enum/array_init.hpp>


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
	using
	result_type
	=
	sanguis::server::damage::basic_array<
		Unit
	>;

	result_type result{
		fcppt::enum_::array_init<
			result_type
		>(
			[](auto)
			{
				return
					Unit(
						0.F
					);
			}
		)
	};

	for(
		auto const &element
		:
		_inits
	)
	{
		result[
			element.type()
		] =
			element.value();
	}

	return
		result;
}

}
}
}

#endif
