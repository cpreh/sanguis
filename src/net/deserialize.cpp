#include "deserialize.hpp"
#include "receive_buffer_source.hpp"
#include "size_type.hpp"
#include "value_type.hpp"
#include "stream_exceptions.hpp"
#include "message_header.hpp"
#include "message_header_size.hpp"
#include "../messages/serialization/deserialize.hpp"
#include "../messages/serialization/endianness.hpp"
#include "../messages/base.hpp"
#include "../messages/global_context.hpp"

#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/io/read.hpp>
#include <fcppt/assert.hpp>

#include <boost/iostreams/stream_buffer.hpp>

#include <istream>

sanguis::messages::auto_ptr
sanguis::net::deserialize(
	net::receive_buffer &_data
)
{
	if(
		_data.read_size() < net::message_header_size
	)
		return messages::auto_ptr();

	typedef boost::iostreams::stream_buffer<
		net::receive_buffer_source
	> stream_buf;

	typedef std::basic_istream<
		net::value_type
	> stream_type;

	net::receive_buffer_source source(
		_data
	);

	stream_buf buf(
		source
	);

	stream_type stream(
		&buf
	);

	net::stream_exceptions(
		stream
	);

	net::message_header const message_size(
		fcppt::io::read<
			net::message_header
		>(
			stream,
			messages::serialization::endianness()
		)
	);
			
	FCPPT_ASSERT(
		message_size > 0
	);

	if(
		_data.read_size()
		< message_size
	)
		return messages::auto_ptr();

	messages::auto_ptr ret(
		messages::serialization::deserialize(
			messages::global_context(),
			stream
		)
	);

	FCPPT_ASSERT(
		ret->size() == message_size
	);

	net::size_type const stream_pos(
		static_cast<
			net::size_type
		>(
			stream.tellg()
		)
	);

	FCPPT_ASSERT(
		ret->size() + net::message_header_size
		== stream_pos
	);

	return ret;
}
