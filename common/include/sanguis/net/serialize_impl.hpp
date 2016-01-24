#ifndef SANGUIS_NET_SERIALIZE_IMPL_HPP_INCLUDED
#define SANGUIS_NET_SERIALIZE_IMPL_HPP_INCLUDED

#include <sanguis/net/message_header.hpp>
#include <alda/serialization/length/serialize.hpp>
#include <alda/message/base_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ostream>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace net
{

template<
	typename AldaType,
	typename Streambuf
>
bool
serialize_impl(
	alda::message::base<
		AldaType
	> const &_message,
	Streambuf &_streambuf
)
{
	alda::serialization::ostream stream(
		&_streambuf
	);

	alda::serialization::length::serialize<
		sanguis::net::message_header
	>(
		stream,
		_message
	);

	return
		!stream.fail();
}

}
}

#endif
