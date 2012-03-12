#include <sanguis/messages/global_context.hpp>
#include <sanguis/messages/types/alda_type.hpp>
#include <alda/serialization/define_context_function.hpp>


ALDA_SERIALIZATION_DEFINE_CONTEXT_FUNCTION(
	sanguis::messages::types::alda_type,
	sanguis::messages::global_context
)
