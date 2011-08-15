#include "deserialize.hpp"
#include "receive_buffer_source.hpp"
#include "size_type.hpp"
#include "value_type.hpp"
#include "stream_exceptions.hpp"
#include "message_header.hpp"
#include "message_header_size.hpp"
#include "message_size.hpp"
#include "../messages/serialization/deserialize.hpp"
#include "../messages/serialization/endianness.hpp"
#include "../messages/base.hpp"
#include "../messages/global_context.hpp"
#include "../exception.hpp"

#include <fcppt/assert/throw.hpp>
#include <fcppt/assert/throw_message.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/io/read.hpp>
#include <fcppt/format.hpp>
#include <fcppt/text.hpp>

#include <boost/iostreams/stream_buffer.hpp>

#include <istream>

sanguis::messages::auto_ptr
sanguis::net::deserialize(
	net::receive_buffer &_data
)
{
	net::receive_buffer::size_type const remaining_size(
		_data.read_size()
	);

	if(
		remaining_size < net::message_header_size
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

	FCPPT_ASSERT_THROW(
		static_cast<
			net::size_type
		>(
			stream.gcount()
		)
		== net::message_header_size,
		sanguis::exception
	);

	FCPPT_ASSERT_THROW(
		message_size > 0,
		sanguis::exception
	);

	FCPPT_ASSERT_THROW_MESSAGE(
		net::message_size(
			message_size
		)
		<= _data.capacity(),
		sanguis::exception,
		(
			fcppt::format(
				FCPPT_TEXT("Received message size %1% is too big for the buffer!")
			)
			% message_size
		).str()
	);

	if(
		remaining_size
		<
		net::message_size(
			message_size
		)
	)
		return messages::auto_ptr();

	messages::auto_ptr ret(
		messages::serialization::deserialize(
			messages::global_context(),
			stream
		)
	);

	FCPPT_ASSERT_THROW(
		ret->size() == message_size,
		sanguis::exception
	);

	net::size_type const bytes_read(
		static_cast<
			net::size_type
		>(
			stream.tellg()
		)
	);

	FCPPT_ASSERT_THROW(
		bytes_read
		==
		net::message_header_size
		+ ret->size(),
		sanguis::exception
	);

	_data.erase(
		bytes_read
	);

	return ret;
}
