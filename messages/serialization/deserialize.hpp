#ifndef SANGUIS_MESSAGES_SERIALIZATION_DESERIALIZE_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_DESERIALIZE_HPP_INCLUDED

#include "istream.hpp"
#include "context_fwd.hpp"
#include "../auto_ptr.hpp"

namespace sanguis
{
namespace messages
{
namespace serialization
{

auto_ptr
deserialize(
	context const &ctx,
	istream &stream
);

}
}
}

#endif
