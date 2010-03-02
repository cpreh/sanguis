#include "deserialize.hpp"
#include "data_type.hpp"
#include "value_type.hpp"
#include "detail/exceptions.hpp"
#include "detail/message_header.hpp"
#include "detail/message_header_size.hpp"
#include "../messages/serialization/deserialize.hpp"
#include "../messages/serialization/endianness.hpp"
#include "../messages/base.hpp"
#include "../messages/global_context.hpp"

#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/io/read.hpp>
#include <fcppt/assert.hpp>

#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream_buffer.hpp>

#include <istream>

sanguis::messages::auto_ptr
sanguis::net::deserialize(
	net::data_type &data
)
{
	if (data.size() < detail::message_header_size)
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

	detail::exceptions(
		stream
	);

	detail::message_header const message_size(
		fcppt::io::read<
			detail::message_header
		>(
			stream,
			messages::serialization::endianness()
		)
	);
			
	FCPPT_ASSERT(message_size > 0);

	if ((data.size() - detail::message_header_size) < message_size)
		return messages::auto_ptr();

	messages::auto_ptr ret(
		messages::serialization::deserialize(
			messages::global_context(),
			stream
		)
	);

	FCPPT_ASSERT(ret->size() == message_size);

	net::data_type::size_type const stream_pos(
		static_cast<
			net::data_type::size_type
		>(
			stream.tellg()
		)
	);

	FCPPT_ASSERT(
		ret->size() + detail::message_header_size
		== stream_pos
	);

	data.erase(
		data.begin(),
		data.begin() + stream_pos
	);

	return ret;
}
