#ifndef SANGUIS_MESSAGES_CLIENT_SERIALIZATION_SERIALIZE_HPP_INCLUDED
#define SANGUIS_MESSAGES_CLIENT_SERIALIZATION_SERIALIZE_HPP_INCLUDED

#include <sanguis/messages/client/base_fwd.hpp>
#include <alda/serialization/ostream.hpp>


namespace sanguis
{
namespace messages
{
namespace client
{
namespace serialization
{

void
serialize(
	alda::serialization::ostream &,
	sanguis::messages::client::base const &
);

}
}
}
}

#endif
