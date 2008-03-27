#include "serialization.hpp"
#include "messages/base.hpp"
#include "messages/add.hpp"

#include "archive.hpp"
#include <boost/serialization/export.hpp>

#include <sge/iostream.hpp>
#include <sstream>
#include <iomanip>
#include <cstddef>
#include <typeinfo>

namespace
{
const std::size_t message_header_size = 4;
}

net::data_type sanguis::deserialize(const net::data_type &data,
	boost::function<void (const message_ptr)> callback)
{
	if (data.size() < message_header_size)
		return data;

	std::basic_istringstream<net::data_type::value_type> 
		ss(data.substr(0,message_header_size));
	std::size_t message_size;
	ss >> std::hex >> message_size;

	if ((data.size()-message_header_size) < message_size)
		return data;

	std::basic_istringstream<net::data_type::value_type> ass(
		data.substr(message_header_size,message_size));
	
	iarchive ar(ass);
	messages::base *unsafe_ptr;
	ar >> unsafe_ptr;
	callback(message_ptr(unsafe_ptr));

	return deserialize(data.substr(message_header_size+message_size),callback);
}

net::data_type sanguis::serialize(const message_ptr m)
{
	typedef std::basic_ostringstream<net::data_type::value_type> sstream;

	sstream ss;
	oarchive oa(ss);
	const messages::base *const ptr = m.get();
	oa << ptr;

	sstream oss;
	oss << std::hex << std::setw(message_header_size) << ss.str().size() << ss.str();
	return oss.str();
}
