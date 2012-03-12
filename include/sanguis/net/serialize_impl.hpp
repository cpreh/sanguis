#ifndef SANGUIS_NET_SERIALIZE_IMPL_HPP_INCLUDED
#define SANGUIS_NET_SERIALIZE_IMPL_HPP_INCLUDED

#include <sanguis/net/value_type.hpp>
#include <sanguis/net/message_header.hpp>
#include <sanguis/messages/base.hpp>
#include <sanguis/messages/serialization/serialize.hpp>
#include <alda/endianness.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/io/write.hpp>
#include <fcppt/truncation_check_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ostream>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace net
{

template<
	typename Streambuf
>
bool
serialize_impl(
	messages::base const &_message,
	Streambuf &_streambuf
)
{
	typedef std::basic_ostream<
		net::value_type
	> stream_type;

	stream_type stream(
		&_streambuf
	);

	net::message_header const header(
		fcppt::truncation_check_cast<
			net::message_header
		>(
			_message.size()
		)
	);

	FCPPT_ASSERT_PRE(
		header > 0
	);

	fcppt::io::write(
		stream,
		header,
		alda::endianness()
	);

	messages::serialization::serialize(
		stream,
		_message
	);

	return !stream.fail();
}

}
}

#endif
