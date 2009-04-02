#ifndef SANGUIS_MESSAGES_SERIALIZATION_READER_IMPL_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_READER_IMPL_HPP_INCLUDED

#include "reader.hpp"
#include "load.hpp"
#include "../make_concrete.hpp"

template<
	typename Msg
>
sanguis::messages::auto_ptr
sanguis::messages::serialization::reader::operator()() const
{
	typedef majutsu::class_<
		Msg,
		majutsu::memory::flat
	> class_type;

	class_type obj;

	typedef typename boost::mpl::remove_if<
		typename class_type::memory_type::types,
		boost::mpl::not_<
			majutsu::is_role<
				boost::mpl::_1
			>
		>
	>::type roles;

	boost::mpl::for_each<
		roles
	>(
		load<class_type>(
			is,
			obj
		)
	);

	return make_concrete(
		obj
	);
}

#endif
