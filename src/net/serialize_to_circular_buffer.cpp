#include "serialize_to_circular_buffer.hpp"
#include "circular_buffer_sink.hpp"
#include "message_size.hpp"
#include "serialize_impl.hpp"
#include <fcppt/assert_message.hpp>
#include <fcppt/format.hpp>
#include <fcppt/text.hpp>
#include <boost/iostreams/stream_buffer.hpp>

bool
sanguis::net::serialize_to_circular_buffer(
	messages::auto_ptr _message,
	net::circular_buffer &_buffer
)
{
	FCPPT_ASSERT_MESSAGE(
		_buffer.capacity()
		>=
		net::message_size(
			_message->size()
		),
		(
			fcppt::format(
				FCPPT_TEXT("Send message size %1% is too big for the buffer!")
			)
			% _message->size()
		).str()
	);

	typedef boost::iostreams::stream_buffer<
		net::circular_buffer_sink
	> stream_buf;

	stream_buf stream(
		_buffer
	);

	return
		net::serialize_impl(
			_message,
			stream
		);
}
