#ifndef SANGUIS_MESSAGES_SERVER_SERIALIZATION_DESERIALIZE_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_SERIALIZATION_DESERIALIZE_HPP_INCLUDED

#include <sanguis/messages/server/unique_ptr.hpp>
#include <alda/serialization/istream_fwd.hpp>


namespace sanguis
{
namespace messages
{
namespace server
{
namespace serialization
{

sanguis::messages::server::unique_ptr
deserialize(
	alda::serialization::istream &
);

}
}
}
}

#endif
