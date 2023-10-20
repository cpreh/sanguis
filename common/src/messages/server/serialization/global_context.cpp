#include <sanguis/messages/server/serialization/context.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/messages/server/serialization/global_context.hpp>
#include <sanguis/messages/server/types/alda_type.hpp>
#include <alda/serialization/define_context_function.hpp>

ALDA_SERIALIZATION_DEFINE_CONTEXT_FUNCTION(
    sanguis::messages::server::types::alda_type,
    sanguis::messages::server::serialization::global_context)
