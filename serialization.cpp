#include "serialization.hpp"
#include "messages/serialization/serialize.hpp"
#include "messages/serialization/deserialize.hpp"
#include "messages/serialization/endianness.hpp"
#include "messages/global_context.hpp"
#include "messages/base.hpp"
#include "net/value_type.hpp"
#include "truncation_check_cast.hpp"

#include <fcppt/container/raw_vector_impl.hpp>
#include <sge/io/read.hpp>
#include <sge/io/write.hpp>
#include <sge/assert.hpp>

#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream_buffer.hpp>
#include <boost/cstdint.hpp>

#include <istream>
#include <ostream>

namespace
{

typedef boost::uint16_t message_header;

sanguis::net::data_type::size_type const
message_header_size = sizeof(message_header);

template<
	typename Stream
>
void
exceptions(
	Stream &stream
)
{
	stream.exceptions(
		std::ios_base::badbit
		| std::ios_base::failbit
		| std::ios_base::eofbit
	);
}

}

sanguis::messages::auto_ptr
sanguis::deserialize(
	net::data_type &data
)
{
	if (data.size() < message_header_size)
		return messages::auto_ptr();

	typedef boost::iostreams::basic_array_source<
		net::value_type
	> array_source;

	typedef boost::iostreams::stream_buffer<
		array_source
	> stream_buf;

	typedef std::basic_istream<
		net::value_type
	> stream_type;

	stream_buf buf(
		data.data(),
		data.data() + data.size()
	);

	stream_type stream(
		&buf
	);

	exceptions(stream);

	message_header const message_size(
		sge::io::read<
			message_header
		>(
			stream,
			messages::serialization::endianness()
		)
	);
			
	SGE_ASSERT(message_size > 0);

	if ((data.size() - message_header_size) < message_size)
		return messages::auto_ptr();

	messages::auto_ptr ret(
		messages::serialization::deserialize(
			messages::global_context(),
			stream
		)
	);

	SGE_ASSERT(ret->size() == message_size);

	net::data_type::size_type const stream_pos(
		static_cast<
			net::data_type::size_type
		>(
			stream.tellg()
		)
	);

	SGE_ASSERT(
		ret->size() + message_header_size
		== stream_pos
	);

	data.erase(
		data.begin(),
		data.begin() + stream_pos
	);

	return ret;
}

void
sanguis::serialize(
	messages::auto_ptr message,
	net::data_type &array
)
{
	SGE_ASSERT(message.get());

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

	exceptions(stream);

	message_header const header(
		truncation_check_cast<
			message_header
		>(
			message->size()
		)
	);

	SGE_ASSERT(header > 0);

	sge::io::write(
		stream,
		header,
		messages::serialization::endianness()
	);

	messages::serialization::serialize(
		stream,
		message
	);
}
