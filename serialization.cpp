#include "serialization.hpp"
#include "messages/serialization/serialize.hpp"
#include "messages/serialization/deserialize.hpp"
#include "messages/global_context.hpp"
#include "messages/base.hpp"

#include <sge/algorithm/copy_n.hpp>

#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream_buffer.hpp>
#include <boost/cstdint.hpp>

#include <iosfwd>
#include <istream>
#include <ostream>

#include <sge/cerr.hpp>

namespace
{

typedef boost::uint16_t message_header;
std::streamsize const message_header_size = sizeof(message_header);

}

sanguis::messages::auto_ptr
sanguis::deserialize(
	net::data_type &data)
{
	if (data.size() < message_header_size)
		return messages::auto_ptr();

	typedef boost::iostreams::basic_array_source<
		net::data_type::value_type
	> array_source;

	typedef boost::iostreams::stream_buffer<
		array_source
	> stream_buf;

	typedef std::basic_istream<
		net::data_type::value_type
	> stream_type;

	stream_buf buf(
		data.data(),
		data.data() + data.size()
	);

	stream_type stream(
		&buf
	);

	// TODO: endianness!
	message_header message_size;
	stream.read(reinterpret_cast<stream_type::char_type *>(&message_size), sizeof(message_size));

	sge::cerr << "read size: " << message_size << '\n';

	if ((data.size() - message_header_size) < message_size)
		return messages::auto_ptr();

	return messages::serialization::deserialize(
		messages::global_context(),
		stream
	);
}

void sanguis::serialize(
	messages::auto_ptr m,
	net::data_type &a)
{
	typedef boost::iostreams::back_insert_device<
		net::data_type
	> back_inserter;

	typedef boost::iostreams::stream_buffer<
		back_inserter
	> stream_buf;

	typedef std::basic_ostream<
		net::data_type::value_type
	> stream_type;

	stream_buf buf(
		a
	);

	stream_type stream(
		&buf
	);

	net::data_type::size_type const header_pos(
		a.size()
	);

	a.resize(
		a.size() + message_header_size
	);

	messages::serialization::serialize(
		stream,
		m
	);

	// TODO: endianness!
	message_header const header(
		a.size() - message_header_size - header_pos
	);
	
	sge::cerr << "write size: " << header << '\n';

	sge::algorithm::copy_n(
		reinterpret_cast<net::data_type::const_pointer>(&header),
		message_header_size,
		&a[0] + header_pos
	);
}
