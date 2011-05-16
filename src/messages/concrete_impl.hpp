#ifndef SANGUIS_MESSAGES_CONCRETE_IMPL_HPP_INCLUDED
#define SANGUIS_MESSAGES_CONCRETE_IMPL_HPP_INCLUDED

#include "concrete.hpp"
#include "message_id.hpp"

template<
	typename T
>
sanguis::messages::concrete<T>::concrete(
	T const &_value
)
:
	value_(_value)
{
}

template<
	typename T
>
sanguis::messages::concrete<T>::~concrete()
{
}

template<
	typename T
>
T const &
sanguis::messages::concrete<T>::value() const
{
	return value_;
}

template<
	typename T
>
sanguis::messages::types::message::type
sanguis::messages::concrete<T>::type() const
{
	return
		static_cast<
			types::message::type
		>(
			messages::message_id<
				typename T::types
			>::type::value
		);
}

template<
	typename T
>
majutsu::const_raw_pointer
sanguis::messages::concrete<T>::data() const
{
	return value_.memory().data();
}

template<
	typename T
>
majutsu::size_type
sanguis::messages::concrete<T>::size() const
{
	return value_.memory().size();
}

#endif
