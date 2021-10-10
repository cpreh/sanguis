#ifndef SANGUIS_MESSAGES_SERVER_SERIALIZATION_GLOBAL_CONTEXT_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_SERIALIZATION_GLOBAL_CONTEXT_HPP_INCLUDED

#include <sanguis/common/symbol.hpp>
#include <sanguis/messages/server/serialization/context_fwd.hpp>

namespace sanguis::messages::server::serialization
{

SANGUIS_COMMON_SYMBOL
sanguis::messages::server::serialization::context &global_context();

}

#endif
