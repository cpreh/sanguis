#include <sanguis/messages/server/connected.hpp>
#include <sanguis/messages/server/instantiate_message.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)
FCPPT_PP_DISABLE_CLANG_WARNING(-Wexit-time-destructors)

SANGUIS_MESSAGES_SERVER_INSTANTIATE_MESSAGE(
	sanguis::messages::server::connected
);

FCPPT_PP_POP_WARNING
