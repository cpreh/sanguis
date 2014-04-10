#ifndef SANGUIS_MESSAGES_CLIENT_SERIALIZATION_DESERIALIZE_HPP_INCLUDED
#define SANGUIS_MESSAGES_CLIENT_SERIALIZATION_DESERIALIZE_HPP_INCLUDED

#include <sanguis/common/symbol.hpp>
#include <sanguis/messages/client/unique_ptr.hpp>
#include <alda/serialization/istream_fwd.hpp>


namespace sanguis
{
namespace messages
{
namespace client
{
namespace serialization
{

SANGUIS_COMMON_SYMBOL
sanguis::messages::client::unique_ptr
deserialize(
	alda::serialization::istream &
);

}
}
}
}

#endif
