#ifndef SANGUIS_NET_SERIALIZE_IMPL_HPP_INCLUDED
#define SANGUIS_NET_SERIALIZE_IMPL_HPP_INCLUDED

#include "value_type.hpp"
#include "message_header.hpp"
#include "../messages/serialization/endianness.hpp"
#include "../messages/serialization/serialize.hpp"
#include "../messages/base.hpp"

#include <fcppt/assert/pre.hpp>
#include <fcppt/io/write.hpp>
#include <fcppt/truncation_check_cast.hpp>

#include <ostream>

namespace sanguis
{
namespace net
{

template<
	typename Streambuf
>
bool
serialize_impl(
	messages::auto_ptr _message,
	Streambuf &_streambuf
)
{
	FCPPT_ASSERT_PRE(
		_message.get()
	);

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
			_message->size()
		)
	);

	FCPPT_ASSERT_PRE(
		header > 0
	);

	fcppt::io::write(
		stream,
		header,
		messages::serialization::endianness()
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
