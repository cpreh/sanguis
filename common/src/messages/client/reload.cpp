#include <sanguis/messages/client/instantiate_message.hpp>
#include <sanguis/messages/client/reload.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)
FCPPT_PP_DISABLE_CLANG_WARNING(-Wexit-time-destructors)

// NOLINTNEXTLINE(cert-err58-cpp,fuchsia-statically-constructed-objects)
SANGUIS_MESSAGES_CLIENT_INSTANTIATE_MESSAGE(
	sanguis::messages::client::reload
);

FCPPT_PP_POP_WARNING
