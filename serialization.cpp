#include "serialization.hpp"
#include "messages/serialization/serialize.hpp"
#include "messages/serialization/deserialize.hpp"
#include "messages/global_context.hpp"
#include "messages/base.hpp"

#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cstddef>

namespace
{
std::streamsize const message_header_size = 2;
}

sanguis::messages::auto_ptr
sanguis::deserialize(
	net::data_type &data)
{
	if (data.size() < message_header_size)
		return messages::auto_ptr();

	typedef std::basic_istringstream<
		net::data_type::value_type
	> stream_type;

	stream_type sss(
		data.substr(
			static_cast<net::data_type::size_type>(
				0),
			static_cast<net::data_type::size_type>(
				message_header_size)));

	std::size_t message_size;
	sss >> std::hex >> message_size;

	if ((data.size()-message_header_size) < message_size)
		return messages::auto_ptr();

	stream_type ss(
		data.substr(
			static_cast<net::data_type::size_type>(
				message_header_size),
			static_cast<net::data_type::size_type>(
				message_size-message_header_size)));
	
	data = data.substr(
		static_cast<net::data_type::size_type>(
			message_size+message_header_size));

	return messages::serialization::deserialize(
		messages::global_context(),
		ss);
}

void sanguis::serialize(
	messages::auto_ptr m,
	net::data_type &a)
{
	typedef std::basic_ostringstream<net::data_type::value_type> stream_type;

	stream_type oss;
	oss
		<< std::hex 
		<< std::setw(message_header_size) 
		<< m->size();

	messages::serialization::serialize(
		oss,
		m
	);

	std::copy(
		oss.str().begin(),
		oss.str().end(),
		std::back_inserter<net::data_type>(a));
}
