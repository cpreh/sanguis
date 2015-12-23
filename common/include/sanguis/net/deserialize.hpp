#ifndef SANGUIS_NET_DESERIALIZE_HPP_INCLUDED
#define SANGUIS_NET_DESERIALIZE_HPP_INCLUDED

#include <sanguis/exception.hpp>
#include <sanguis/net/deserialize_message_function.hpp>
#include <sanguis/net/message_header.hpp>
#include <sanguis/net/message_header_size.hpp>
#include <sanguis/net/message_size.hpp>
#include <sanguis/net/stream_exceptions.hpp>
#include <alda/message/base_decl.hpp>
#include <alda/message/base_unique_ptr.hpp>
#include <alda/serialization/endianness.hpp>
#include <alda/net/size_type.hpp>
#include <alda/net/value_type.hpp>
#include <alda/net/buffer/circular_receive/object.hpp>
#include <alda/net/buffer/circular_receive/source.hpp>
#include <fcppt/format.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/assert/throw.hpp>
#include <fcppt/assert/throw_message.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/io/read.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/iostreams/stream_buffer.hpp>
#include <ios>
#include <istream>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace net
{

template<
	typename AldaType
>
fcppt::optional<
	alda::message::base_unique_ptr<
		AldaType
	>
>
deserialize(
	alda::net::buffer::circular_receive::object &_data,
	sanguis::net::deserialize_message_function<
		AldaType
	> const _deserialize_message
)
{
	typedef
	alda::message::base_unique_ptr<
		AldaType
	>
	unique_ptr;

	typedef
	fcppt::optional<
		unique_ptr
	>
	result_type;

	alda::net::buffer::circular_receive::object::size_type const remaining_size(
		_data.read_size()
	);

	if(
		remaining_size
		<
		sanguis::net::message_header_size::value
	)
		return
			result_type();

	typedef boost::iostreams::stream_buffer<
		alda::net::buffer::circular_receive::source
	> stream_buf;

	typedef std::basic_istream<
		alda::net::value_type
	> stream_type;

	alda::net::buffer::circular_receive::source source(
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
		FCPPT_ASSERT_OPTIONAL_ERROR(
			fcppt::io::read<
				sanguis::net::message_header
			>(
				stream,
				alda::serialization::endianness()
			)
		)
	);

	FCPPT_ASSERT_THROW(
		fcppt::cast::size<
			alda::net::size_type
		>(
			fcppt::cast::to_unsigned(
				stream.gcount()
			)
		)
		==
		sanguis::net::message_header_size::value
		,
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
		return
			result_type();

	unique_ptr ret(
		_deserialize_message(
			stream
		)
	);

	FCPPT_ASSERT_THROW(
		ret->size() == message_size,
		sanguis::exception
	);

	alda::net::size_type const bytes_read(
		fcppt::cast::size<
			alda::net::size_type
		>(
			fcppt::cast::to_unsigned(
				static_cast<
					std::streamoff
				>(
					stream.tellg()
				)
			)
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
		result_type(
			std::move(
				ret
			)
		);
}

}
}

#endif
