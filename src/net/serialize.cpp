#include "serialize.hpp"
#include "data_buffer.hpp"
#include "value_type.hpp"
#include "message_header.hpp"
#include "message_header_size.hpp"
#include "stream_exceptions.hpp"
#include "../messages/serialization/endianness.hpp"
#include "../messages/serialization/serialize.hpp"
#include "../messages/base.hpp"

#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/io/write.hpp>
#include <fcppt/truncation_check_cast.hpp>
#include <fcppt/assert.hpp>

#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream_buffer.hpp>

#include <ostream>

void
sanguis::net::serialize(
	messages::auto_ptr _message,
	net::data_buffer &_data
)
{
	FCPPT_ASSERT(
		_message.get()
	);

	FCPPT_ASSERT(
		_data.empty()
	);

	typedef boost::iostreams::back_insert_device<
		net::data_buffer
	> back_inserter;

	typedef boost::iostreams::stream_buffer<
		back_inserter
	> stream_buf;

	typedef std::basic_ostream<
		net::value_type
	> stream_type;

	stream_buf buf(
		_data
	);

	stream_type stream(
		&buf
	);

	net::stream_exceptions(
		stream
	);

	net::message_header const header(
		fcppt::truncation_check_cast<
			net::message_header
		>(
			_message->size()
		)
	);

	FCPPT_ASSERT(
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
}
