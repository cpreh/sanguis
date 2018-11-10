#ifndef SANGUIS_MESSAGES_SERVER_MAGAZINE_REMAINING_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_MAGAZINE_REMAINING_HPP_INCLUDED

#include <sanguis/messages/adapted_types/is_primary_weapon.hpp>
#include <sanguis/messages/adapted_types/magazine_size.hpp>
#include <sanguis/messages/server/magazine_remaining_fwd.hpp>
#include <sanguis/messages/server/declare_message.hpp>
#include <alda/bindings/record_variadic.hpp>
#include <alda/message/object.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/record/element.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wweak-template-vtables)

SANGUIS_MESSAGES_SERVER_DECLARE_MESSAGE(
	sanguis::messages::server::magazine_remaining
);

FCPPT_PP_POP_WARNING

#endif
