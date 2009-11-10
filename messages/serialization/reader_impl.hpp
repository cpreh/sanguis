#ifndef SANGUIS_MESSAGES_SERIALIZATION_READER_IMPL_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_READER_IMPL_HPP_INCLUDED

#include "reader.hpp"
#include "read_element_impl.hpp"
#include "../make_concrete.hpp"
#include <majutsu/is_role.hpp>
#include <boost/mpl/filter_view.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/for_each.hpp>

template<
	typename Msg
>
sanguis::messages::auto_ptr
sanguis::messages::serialization::reader::operator()() const
{
	Msg obj;

	boost::mpl::for_each<
		boost::mpl::filter_view<
			typename Msg::memory_type::types,
			majutsu::is_role<
				boost::mpl::_1
			>
		>
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
