#ifndef SANGUIS_NET_DESERIALIZE_MESSAGE_FUNCTION_HPP_INCLUDED
#define SANGUIS_NET_DESERIALIZE_MESSAGE_FUNCTION_HPP_INCLUDED

#include <alda/message/base_unique_ptr.hpp>
#include <alda/serialization/istream_fwd.hpp>


namespace sanguis
{
namespace net
{

template<
	typename AldaType
>
using
deserialize_message_function
=
alda::message::base_unique_ptr<
	AldaType
>
(*)(
	alda::serialization::istream &
);

}
}

#endif
