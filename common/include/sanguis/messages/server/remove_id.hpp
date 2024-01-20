#ifndef SANGUIS_MESSAGES_SERVER_REMOVE_ID_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_REMOVE_ID_HPP_INCLUDED

#include <sanguis/messages/server/declare_message.hpp>
#include <sanguis/messages/server/remove_id_fwd.hpp> // IWYU pragma: export
#include <alda/bindings/unit.hpp> // IWYU pragma: keep
#include <alda/message/object.hpp> // IWYU pragma: keep
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wweak-template-vtables)

SANGUIS_MESSAGES_SERVER_DECLARE_MESSAGE(sanguis::messages::server::remove_id);

FCPPT_PP_POP_WARNING

#endif
