#include "serialize_to_circular_buffer.hpp"
#include "circular_buffer_sink.hpp"
#include "serialize_impl.hpp"
#include <boost/iostreams/stream_buffer.hpp>

bool
sanguis::net::serialize_to_circular_buffer(
	messages::auto_ptr _message,
	net::circular_buffer &_buffer
)
{
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
