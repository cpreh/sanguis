#ifndef SANGUIS_MESSAGES_SERIALIZATION_SERIALIZE_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_SERIALIZE_HPP_INCLUDED

#include <sanguis/messages/base_fwd.hpp>
#include <alda/serialization/ostream.hpp>


namespace sanguis
{
namespace messages
{
namespace serialization
{

void
serialize(
	alda::serialization::ostream &,
	sanguis::messages::base const &
);

}
}
}

#endif
