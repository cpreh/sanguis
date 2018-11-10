#include <sanguis/messages/server/instantiate_message.hpp>
#include <sanguis/messages/server/speed.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)
FCPPT_PP_DISABLE_CLANG_WARNING(-Wexit-time-destructors)

SANGUIS_MESSAGES_SERVER_INSTANTIATE_MESSAGE(
	sanguis::messages::server::speed
);

FCPPT_PP_POP_WARNING
