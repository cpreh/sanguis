#ifndef SANGUIS_MESSAGES_CLIENT_CONSOLE_COMMAND_HPP_INCLUDED
#define SANGUIS_MESSAGES_CLIENT_CONSOLE_COMMAND_HPP_INCLUDED

#include <sanguis/messages/adapted_types/string_vector.hpp> // IWYU pragma: keep
#include <sanguis/messages/client/console_command_fwd.hpp> // IWYU pragma: export
#include <sanguis/messages/client/declare_message.hpp>
#include <alda/bindings/record_variadic.hpp> // IWYU pragma: keep
#include <alda/message/object.hpp> // IWYU pragma: keep
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/record/element.hpp> // IWYU pragma: keep

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wweak-template-vtables)

SANGUIS_MESSAGES_CLIENT_DECLARE_MESSAGE(sanguis::messages::client::console_command);

FCPPT_PP_POP_WARNING

#endif
