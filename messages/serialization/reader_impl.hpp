#ifndef SANGUIS_MESSAGES_SERIALIZATION_READER_IMPL_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_READER_IMPL_HPP_INCLUDED

#include "reader.hpp"
#include "read_element_impl.hpp"
#include "../make_concrete.hpp"

template<
	typename Msg
>
sanguis::messages::auto_ptr
sanguis::messages::serialization::reader::operator()() const
{
	typedef typename boost::mpl::remove_if<
		typename Msg::memory_type::types,
		boost::mpl::not_<
			majutsu::is_role<
				boost::mpl::_1
			>
		>
	>::type roles;

	Msg obj;

	boost::mpl::for_each<
		roles
	>(
		read_element<Msg>(
			is,
			obj
		)
	);

	return make_concrete(
		obj
	);
}

#endif
