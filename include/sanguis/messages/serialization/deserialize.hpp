#ifndef SANGUIS_MESSAGES_SERIALIZATION_DESERIALIZE_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_DESERIALIZE_HPP_INCLUDED

#include <sanguis/messages/serialization/istream.hpp>
#include <sanguis/messages/serialization/context_fwd.hpp>
#include <sanguis/messages/auto_ptr.hpp>

namespace sanguis
{
namespace messages
{
namespace serialization
{

messages::auto_ptr
deserialize(
	serialization::context const &,
	serialization::istream &
);

}
}
}

#endif
