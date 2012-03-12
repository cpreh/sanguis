#ifndef SANGUIS_MESSAGES_SERIALIZATION_DESERIALIZE_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_DESERIALIZE_HPP_INCLUDED

#include <sanguis/messages/serialization/context_fwd.hpp>
#include <sanguis/messages/auto_ptr.hpp>
#include <alda/serialization/istream.hpp>


namespace sanguis
{
namespace messages
{
namespace serialization
{

sanguis::messages::auto_ptr
deserialize(
	sanguis::messages::serialization::context const &,
	alda::serialization::istream &
);

}
}
}

#endif
