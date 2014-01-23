#ifndef SANGUIS_MESSAGES_SERVER_SERIALIZATION_SERIALIZE_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_SERIALIZATION_SERIALIZE_HPP_INCLUDED

#include <sanguis/messages/server/base_fwd.hpp>
#include <alda/serialization/ostream.hpp>


namespace sanguis
{
namespace messages
{
namespace server
{
namespace serialization
{

void
serialize(
	alda::serialization::ostream &,
	sanguis::messages::server::base const &
);

}
}
}
}

#endif
