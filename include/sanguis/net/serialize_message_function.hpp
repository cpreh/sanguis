#ifndef SANGUIS_NET_SERIALIZE_MESSAGE_FUNCTION_HPP_INCLUDED
#define SANGUIS_NET_SERIALIZE_MESSAGE_FUNCTION_HPP_INCLUDED

#include <alda/message/base_fwd.hpp>
#include <alda/serialization/ostream.hpp>


namespace sanguis
{
namespace net
{

template<
	typename AldaType
>
using
serialize_message_function
=
void
(*)(
	alda::serialization::ostream &,
	alda::message::base<
		AldaType
	> const &
);

}
}

#endif
