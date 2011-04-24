#ifndef SANGUIS_MESSAGES_SERIALIZATION_READ_ELEMENT_IMPL_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_READ_ELEMENT_IMPL_HPP_INCLUDED

#include "read_element.hpp"
#include "load.hpp"
#include <majutsu/access_role.hpp>

template<
	typename Class
>
sanguis::messages::serialization::read_element<Class>::read_element(
	std::istream &_is,
	Class &_obj
)
:
	is_(_is),
	obj_(_obj)
{
}

template<
	typename Class
>
template<
	typename Role
>
void
sanguis::messages::serialization::read_element<Class>::operator()(
	Role &
) const
{
	obj_. template set<
		typename Role::alias
	>(
		messages::serialization::load<
			typename majutsu::access_role<
				Role
			>::type
		>::get(
			is_
		)
	);
}

#endif
