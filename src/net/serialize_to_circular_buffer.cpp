#include <sanguis/messages/base.hpp>
#include <sanguis/net/circular_buffer_sink.hpp>
#include <sanguis/net/message_size.hpp>
#include <sanguis/net/serialize_impl.hpp>
#include <sanguis/net/serialize_to_circular_buffer.hpp>
#include <alda/net/buffer/circular_send/object.hpp>
#include <fcppt/assert/pre_message.hpp>
#include <fcppt/format.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/iostreams/stream_buffer.hpp>
#include <fcppt/config/external_end.hpp>


bool
sanguis::net::serialize_to_circular_buffer(
	sanguis::messages::base const &_message,
	alda::net::buffer::circular_send::object &_buffer
)
{
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
	);

	typedef boost::iostreams::stream_buffer<
		sanguis::net::circular_buffer_sink
	> stream_buf;

	stream_buf stream(
		_buffer
	);

	return
		sanguis::net::serialize_impl(
			_message,
			stream
		);
}
