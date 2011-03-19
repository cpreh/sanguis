#include "serialize_to_data_buffer.hpp"
#include "serialize_impl.hpp"
#include "data_buffer.hpp"
#include <fcppt/container/raw_vector_impl.hpp>
#include <boost/iostreams/stream_buffer.hpp>
#include <boost/iostreams/device/back_inserter.hpp>

bool
sanguis::net::serialize_to_data_buffer(
	messages::auto_ptr _message,
	net::data_buffer &_buffer
)
{
	typedef boost::iostreams::back_insert_device<
		net::data_buffer
	> sink;

	typedef boost::iostreams::stream_buffer<
		sink
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
