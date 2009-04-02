#ifndef SANGUIS_MESSAGES_CONCRETE_IMPL_HPP_INCLUDED
#define SANGUIS_MESSAGES_CONCRETE_IMPL_HPP_INCLUDED

#include "concrete.hpp"

template<
	typename T
>
sanguis::messages::concrete<T>::concrete(
	T const &value_)
:
	value_(value_)
{}
	
T const &
sanguis::messages::concrete<T>::value() const
{
	return value_;
}

majutsu::const_raw_pointer
sanguis::messages::concrete<T>::data() const
{
	return value_.memory().data();
}

majutsu::size_type
sanguis::messages::concrete<T>::size() const
{
	return value_.memory().size();
}
