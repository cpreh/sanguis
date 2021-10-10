#ifndef SANGUIS_MESSAGES_SERVER_EXPERIENCE_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_EXPERIENCE_HPP_INCLUDED

#include <sanguis/messages/adapted_types/exp.hpp>
#include <sanguis/messages/server/declare_message.hpp>
#include <sanguis/messages/server/experience_fwd.hpp>
#include <alda/message/object.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wweak-template-vtables)

SANGUIS_MESSAGES_SERVER_DECLARE_MESSAGE(sanguis::messages::server::experience);

FCPPT_PP_POP_WARNING

#endif
