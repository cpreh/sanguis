#include <sanguis/messages/server/serialization/details.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/messages/server/types/alda_type.hpp>
#include <alda/serialization/instantiate_details.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wweak-template-vtables)

ALDA_SERIALIZATION_INSTANTIATE_DETAILS(sanguis::messages::server::types::alda_type);

FCPPT_PP_POP_WARNING
