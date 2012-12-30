#include <sanguis/net/deserialize.hpp>
#include <sanguis/net/receive_buffer_source.hpp>
#include <sanguis/net/stream_exceptions.hpp>
#include <sanguis/net/message_header.hpp>
#include <sanguis/net/message_header_size.hpp>
#include <sanguis/net/message_size.hpp>
#include <sanguis/messages/serialization/deserialize.hpp>
#include <sanguis/messages/base.hpp>
#include <sanguis/messages/global_context.hpp>
#include <sanguis/exception.hpp>
#include <alda/endianness.hpp>
#include <alda/net/size_type.hpp>
#include <alda/net/value_type.hpp>
#include <alda/net/buffer/circular_receive/object.hpp>
#include <fcppt/assert/throw.hpp>
#include <fcppt/assert/throw_message.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/io/read.hpp>
#include <fcppt/format.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/iostreams/stream_buffer.hpp>
#include <istream>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::messages::auto_ptr
sanguis::net::deserialize(
	alda::net::buffer::circular_receive::object &_data
)
{
	alda::net::buffer::circular_receive::object::size_type const remaining_size(
		_data.read_size()
	);

	if(
		remaining_size < sanguis::net::message_header_size::value
	)
		return sanguis::messages::auto_ptr();

	typedef boost::iostreams::stream_buffer<
		sanguis::net::receive_buffer_source
	> stream_buf;

	typedef std::basic_istream<
		alda::net::value_type
	> stream_type;

	sanguis::net::receive_buffer_source source(
		_data
	);

	stream_buf buf(
		source
	);

	stream_type stream(
		&buf
	);

	sanguis::net::stream_exceptions(
		stream
	);

	sanguis::net::message_header const message_size(
		*fcppt::io::read<
			sanguis::net::message_header
		>(
			stream,
			alda::endianness()
		)
	);

	FCPPT_ASSERT_THROW(
		static_cast<
			alda::net::size_type
		>(
			stream.gcount()
		)
		== sanguis::net::message_header_size::value,
		sanguis::exception
	);

	FCPPT_ASSERT_THROW(
		message_size > 0,
		sanguis::exception
	);

	FCPPT_ASSERT_THROW_MESSAGE(
		sanguis::net::message_size(
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
		sanguis::net::message_size(
			message_size
		)
	)
		return sanguis::messages::auto_ptr();

	sanguis::messages::auto_ptr ret(
		sanguis::messages::serialization::deserialize(
			sanguis::messages::global_context(),
			stream
		)
	);

	FCPPT_ASSERT_THROW(
		ret->size() == message_size,
		sanguis::exception
	);

	alda::net::size_type const bytes_read(
		static_cast<
			alda::net::size_type
		>(
			stream.tellg()
		)
	);

	FCPPT_ASSERT_THROW(
		bytes_read
		==
		sanguis::net::message_header_size::value
		+ ret->size(),
		sanguis::exception
	);

	_data.erase(
		bytes_read
	);

	return
		std::move(
			ret
		);
}
