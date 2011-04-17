#ifndef SANGUIS_MESSAGES_SERIALIZATION_MAKE_OBJECT_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_MAKE_OBJECT_HPP_INCLUDED

#include "istream.hpp"
#include "read_element_impl.hpp"
#include <majutsu/is_role.hpp>
#include <boost/mpl/filter_view.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/placeholders.hpp>

namespace sanguis
{
namespace messages
{
namespace serialization
{

template<
	typename Msg
>
Msg const
make_object(
	serialization::istream &_stream
)
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
		serialization::read_element<
			Msg
		>(
			_stream,
			obj
		)
	);

	return obj;
}

}
}
}

#endif
