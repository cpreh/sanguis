#ifndef SANGUIS_SERIALIZATION_HPP_INCLUDED
#define SANGUIS_SERIALIZATION_HPP_INCLUDED

#include "net/data_type.hpp"
#include "messages/auto_ptr.hpp"

namespace sanguis
{

messages::auto_ptr
deserialize(
	net::data_type &data);

void
serialize(
	messages::auto_ptr,
	net::data_type &);

}

#endif 
