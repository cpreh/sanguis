#ifndef SANGUIS_MESSAGES_SERVER_SERIALIZATION_CONTEXT_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_SERIALIZATION_CONTEXT_FWD_HPP_INCLUDED

#include <sanguis/messages/server/types/alda_type.hpp>
#include <alda/serialization/context_fwd.hpp>


namespace sanguis
{
namespace messages
{
namespace server
{
namespace serialization
{

using
context
=
alda::serialization::context<
	sanguis::messages::server::types::alda_type
>;

}
}
}
}

#endif
