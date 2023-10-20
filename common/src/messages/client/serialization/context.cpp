#include <sanguis/messages/client/serialization/context.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/messages/client/serialization/details.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/messages/client/types/alda_type.hpp>
#include <alda/serialization/instantiate_context.hpp>

ALDA_SERIALIZATION_INSTANTIATE_CONTEXT(sanguis::messages::client::types::alda_type);
