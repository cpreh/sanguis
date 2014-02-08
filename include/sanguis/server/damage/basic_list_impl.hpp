#ifndef SANGUIS_SERVER_DAMAGE_BASIC_LIST_IMPL_HPP_INCLUDED
#define SANGUIS_SERVER_DAMAGE_BASIC_LIST_IMPL_HPP_INCLUDED

#include <sanguis/server/damage/basic_list_decl.hpp>
#include <sanguis/server/damage/basic_meta_decl.hpp>
#include <fcppt/algorithm/array_init.hpp>


template<
	typename Unit
>
sanguis::server::damage::basic_list<
	Unit
>::basic_list(
	Unit const _value
)
:
	array_{
		fcppt::algorithm::array_init<
			typename
			array_type::internal
		>(
			_value
		)
	}
{
}

template<
	typename Unit
>
sanguis::server::damage::basic_list<
	Unit
>::basic_list(
	meta_initializer_list const &_init_values
)
:
	basic_list(
		Unit(
			0.f
		)
	)
{
	for(
		auto const &element
		:
		_init_values
	)
		array_[
			element.type()
		] =
			element.value();
}

template<
	typename Unit
>
sanguis::server::damage::basic_list<
	Unit
>::
operator typename sanguis::server::damage::basic_list<
	Unit
>::array_type() const
{
	return
		array_;
}

#endif
