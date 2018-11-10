#include <sanguis/messages/server/serialization/context.hpp>
#include <sanguis/messages/server/serialization/details.hpp>
#include <sanguis/messages/server/types/alda_type.hpp>
#include <alda/serialization/instantiate_context.hpp>


ALDA_SERIALIZATION_INSTANTIATE_CONTEXT(
	sanguis::messages::server::types::alda_type
);
