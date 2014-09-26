#ifndef SANGUIS_NET_SERIALIZE_IMPL_HPP_INCLUDED
#define SANGUIS_NET_SERIALIZE_IMPL_HPP_INCLUDED

#include <sanguis/net/message_header.hpp>
#include <sanguis/net/serialize_message_function.hpp>
#include <alda/endianness.hpp>
#include <alda/message/base_decl.hpp>
#include <alda/net/value_type.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/cast/truncation_check.hpp>
#include <fcppt/io/write.hpp>
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
	Streambuf &_streambuf,
	sanguis::net::serialize_message_function<
		AldaType
	> const &_serialize_message
)
{
	typedef
	std::basic_ostream<
		alda::net::value_type
	>
	stream_type;

	stream_type stream(
		&_streambuf
	);

	sanguis::net::message_header const header(
		fcppt::cast::truncation_check<
			sanguis::net::message_header
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

	_serialize_message(
		stream,
		_message
	);

	return
		!stream.fail();
}

}
}

#endif
