#ifndef SANGUIS_NET_SERIALIZE_TO_CIRCULAR_BUFFER_HPP_INCLUDED
#define SANGUIS_NET_SERIALIZE_TO_CIRCULAR_BUFFER_HPP_INCLUDED

#include <sanguis/net/message_size.hpp>
#include <sanguis/net/serialize_impl.hpp>
#include <sanguis/net/serialize_message_function.hpp>
#include <alda/message/base_decl.hpp>
#include <alda/net/buffer/circular_send/object.hpp>
#include <alda/net/buffer/circular_send/sink.hpp>
#include <fcppt/format.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/pre_message.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/iostreams/stream_buffer.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace net
{

template<
	typename AldaType
>
bool
serialize_to_circular_buffer(
	alda::message::base<
		AldaType
	> const &_message,
	alda::net::buffer::circular_send::object &_buffer,
	sanguis::net::serialize_message_function<
		AldaType
	> const &_serialize_message
)
{
	// FIXME: Use alda's serialization
/*
	FCPPT_ASSERT_PRE_MESSAGE(
		_buffer.get().capacity()
		>=
		sanguis::net::message_size(
			_message.size()
		),
		(
			fcppt::format(
				FCPPT_TEXT("Send message size %1% is too big for the buffer!")
			)
			% _message.size()
		).str()
	);*/

	typedef
	boost::iostreams::stream_buffer<
		alda::net::buffer::circular_send::sink
	>
	stream_buf;

	stream_buf stream(
		_buffer
	);

	return
		sanguis::net::serialize_impl(
			_message,
			stream,
			_serialize_message
		);
}

}
}

#endif
