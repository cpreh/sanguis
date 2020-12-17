#ifndef SANGUIS_MESSAGES_CLIENT_SERIALIZATION_CONTEXT_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_CLIENT_SERIALIZATION_CONTEXT_FWD_HPP_INCLUDED

#include <sanguis/messages/client/types/alda_type.hpp>
#include <alda/serialization/context_fwd.hpp>


namespace sanguis
{
namespace messages
{
namespace client
{
namespace serialization
{

using
context
=
alda::serialization::context<
	sanguis::messages::client::types::alda_type
>;

}
}
}
}

#endif
