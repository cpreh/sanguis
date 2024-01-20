#ifndef SANGUIS_MESSAGES_SERVER_SERIALIZATION_CONTEXT_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_SERIALIZATION_CONTEXT_HPP_INCLUDED

#include <sanguis/messages/server/serialization/context_fwd.hpp> // IWYU pragma: export
#include <sanguis/messages/server/types/alda_type.hpp>
#include <alda/serialization/declare_context.hpp> // IWYU pragma: keep

ALDA_SERIALIZATION_DECLARE_CONTEXT(sanguis::messages::server::types::alda_type);

#endif
