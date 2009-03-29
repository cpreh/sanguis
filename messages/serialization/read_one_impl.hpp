#ifndef SANGUIS_MESSAGES_SERIALIZATION_READ_ONE_IMPL_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_READ_ONE_IMPL_HPP_INCLUDED

#include "read_one.hpp"
#include "load.hpp"

template<
	typename Class
>
sanguis::messages::serialization::read_one<Class>::read_one(
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
sanguis::messages::serialization::read_one<Class>::operator()(
	Role &) const
{
	typedef typename Role::type type;

	typename type::type ret(
		load<type>::get(is)
	);

	obj. template set<type>(ret);
		//obj. template set<type>(load<type>::get(is));
}
