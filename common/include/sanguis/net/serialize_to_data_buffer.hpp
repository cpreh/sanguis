#ifndef SANGUIS_NET_SERIALIZE_TO_DATA_BUFFER_HPP_INCLUDED
#define SANGUIS_NET_SERIALIZE_TO_DATA_BUFFER_HPP_INCLUDED

#include <sanguis/net/data_buffer.hpp>
#include <sanguis/net/message_header.hpp>
#include <alda/message/base_fwd.hpp>
#include <alda/serialization/length/serialize.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/iostreams/stream_buffer.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace net
{

template<
	typename AldaType
>
void
serialize_to_data_buffer(
	alda::message::base<
		AldaType
	> const &_message,
	sanguis::net::data_buffer &_buffer
)
{
	typedef
	boost::iostreams::back_insert_device<
		sanguis::net::data_buffer
	>
	sink;

	boost::iostreams::stream_buffer<
		sink
	> stream_buf(
		_buffer
	);

	alda::serialization::ostream stream(
		&stream_buf
	);

	alda::serialization::length::serialize<
		sanguis::net::message_header
	>(
		stream,
		_message
	);
}

}
}

#endif
