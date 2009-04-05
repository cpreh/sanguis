#ifndef SANGUIS_MESSAGES_SERIALIZATION_READ_ELEMENT_IMPL_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_READ_ELEMENT_IMPL_HPP_INCLUDED

#include "read_element.hpp"
#include "load.hpp"

template<
	typename Class
>
sanguis::messages::serialization::read_element<Class>::read_element(
	std::istream &is,
	Class &obj)
:
	is(is),
	obj(obj)
{}

template<
	typename Class
>
template<
	typename Role
>
void
sanguis::messages::serialization::read_element<Class>::operator()(
	Role &) const
{
	obj. template set<
		typename Role::alias
	>(
		load<typename Role::type>::get(is)
	);
}

#endif
