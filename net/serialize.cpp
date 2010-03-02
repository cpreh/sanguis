#include "serialize.hpp"
#include "data_type.hpp"
#include "value_type.hpp"
#include "detail/message_header.hpp"
#include "detail/exceptions.hpp"
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
	messages::auto_ptr message,
	net::data_type &array
)
{
	FCPPT_ASSERT(message.get());

	typedef boost::iostreams::back_insert_device<
		net::data_type
	> back_inserter;

	typedef boost::iostreams::stream_buffer<
		back_inserter
	> stream_buf;

	typedef std::basic_ostream<
		net::value_type
	> stream_type;

	stream_buf buf(
		array
	);

	stream_type stream(
		&buf
	);

	detail::exceptions(
		stream
	);

	detail::message_header const header(
		fcppt::truncation_check_cast<
			detail::message_header
		>(
			message->size()
		)
	);

	FCPPT_ASSERT(header > 0);

	fcppt::io::write(
		stream,
		header,
		messages::serialization::endianness()
	);

	messages::serialization::serialize(
		stream,
		message
	);
}
