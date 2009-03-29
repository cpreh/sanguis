#ifndef SANGUIS_MESSAGES_SERIALIZATION_SERIALIZE_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_SERIALIZE_HPP_INCLUDED

#include "ostream.hpp"

namespace sanguis
{
namespace messages
{
namespace serialization
{

void serialize(
	ostream &,
	auto_ptr);

}
}
}

#endif
