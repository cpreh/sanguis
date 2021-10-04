#ifndef SANGUIS_MESSAGES_CLIENT_SERIALIZATION_GLOBAL_CONTEXT_HPP_INCLUDED
#define SANGUIS_MESSAGES_CLIENT_SERIALIZATION_GLOBAL_CONTEXT_HPP_INCLUDED

#include <sanguis/common/symbol.hpp>
#include <sanguis/messages/client/serialization/context_fwd.hpp>


namespace sanguis::messages::client::serialization
{

SANGUIS_COMMON_SYMBOL
sanguis::messages::client::serialization::context &
global_context();

}

#endif
