#ifndef SANGUIS_MESSAGES_SERIALIZATION_DISPATCHER_IMPL_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_DISPATCHER_IMPL_HPP_INCLUDED

#include <sanguis/messages/serialization/dispatcher.hpp>
#include <sanguis/messages/serialization/reader.hpp>

template<
	typename T
>
sanguis::messages::serialization::dispatcher<T>::dispatcher()
{
}

template<
	typename T
>
sanguis::messages::serialization::dispatcher<T>::~dispatcher()
{
}

template<
	typename T
>
sanguis::messages::auto_ptr
sanguis::messages::serialization::dispatcher<T>::on_dispatch(
	serialization::reader const &_reader
) const
{
	return _reader.operator()<T>();
}

#endif
