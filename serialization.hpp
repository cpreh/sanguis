#ifndef SERIALIZATION_HPP
#define SERIALIZATION_HPP

#include "net/types.hpp"
#include "messages/base.hpp"
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstddef>

namespace sanguis
{
net::data_type deserialize(const net::data_type &data,
	boost::function<void (const message_ptr)> callback);
net::data_type serialize(const message_ptr);
}

#endif 
