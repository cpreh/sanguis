#ifndef SANGUIS_MESSAGES_SERVER_BASE_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_BASE_HPP_INCLUDED

#include <sanguis/messages/server/base_fwd.hpp>
#include <sanguis/messages/server/types/alda_type.hpp>
#include <alda/message/declare_base.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wweak-template-vtables)

ALDA_MESSAGE_DECLARE_BASE(
	sanguis::messages::server::types::alda_type
);

FCPPT_PP_POP_WARNING

#endif
