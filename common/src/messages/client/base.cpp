#include <sanguis/messages/client/base.hpp>
#include <sanguis/messages/client/types/alda_type.hpp>
#include <alda/message/instantiate_base.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)
FCPPT_PP_DISABLE_CLANG_WARNING(-Wexit-time-destructors)

ALDA_MESSAGE_INSTANTIATE_BASE(
	sanguis::messages::client::types::alda_type
);

FCPPT_PP_POP_WARNING
