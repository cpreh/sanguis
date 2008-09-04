#ifndef SANGUIS_SERIALIZATION_HPP_INCLUDED
#define SANGUIS_SERIALIZATION_HPP_INCLUDED

#include "net/types.hpp"
#include "messages/base.hpp"
#include <boost/function.hpp>

namespace sanguis
{

typedef boost::function<void (messages::auto_ptr)> deserialize_callback;

net::data_type deserialize(
	net::data_type const &data,
	deserialize_callback const &callback);

net::data_type serialize(messages::auto_ptr);

}

#endif 
