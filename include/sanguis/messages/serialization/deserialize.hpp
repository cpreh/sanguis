#ifndef SANGUIS_MESSAGES_SERIALIZATION_DESERIALIZE_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_DESERIALIZE_HPP_INCLUDED

#include <sanguis/messages/unique_ptr.hpp>
#include <sanguis/messages/serialization/context_fwd.hpp>
#include <alda/serialization/istream_fwd.hpp>


namespace sanguis
{
namespace messages
{
namespace serialization
{

sanguis::messages::unique_ptr
deserialize(
	sanguis::messages::serialization::context const &,
	alda::serialization::istream &
);

}
}
}

#endif
