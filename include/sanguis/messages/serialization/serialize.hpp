#ifndef SANGUIS_MESSAGES_SERIALIZATION_SERIALIZE_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_SERIALIZE_HPP_INCLUDED

#include <sanguis/messages/serialization/ostream.hpp>
#include <sanguis/messages/auto_ptr.hpp>

namespace sanguis
{
namespace messages
{
namespace serialization
{

void
serialize(
	serialization::ostream &,
	messages::auto_ptr
);

}
}
}

#endif
