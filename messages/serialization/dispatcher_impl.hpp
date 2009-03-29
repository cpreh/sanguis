#ifndef SANGUIS_MESSAGES_SERIALIZATION_DISPATCHER_IMPL_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_DISPATCHER_IMPL_HPP_INCLUDED

#include "dispatcher.hpp"
#include "reader.hpp"

template<
	typename T
>
sanguis::messages::auto_ptr
sanguis::messages::serialization::dispatcher<T>::on_dispatch(
	reader const &d) const
{
	return d.operator()<T>();
}

#endif
