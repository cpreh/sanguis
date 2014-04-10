#include <sanguis/messages/client/serialization/global_context.hpp>
#include <sanguis/messages/client/types/alda_type.hpp>
#include <alda/serialization/define_context_function.hpp>


ALDA_SERIALIZATION_DEFINE_CONTEXT_FUNCTION(
	sanguis::messages::client::types::alda_type,
	sanguis::messages::client::serialization::global_context
)
