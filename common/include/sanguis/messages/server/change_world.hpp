#ifndef SANGUIS_MESSAGES_SERVER_CHANGE_WORLD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_CHANGE_WORLD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/bool.hpp>
#include <sanguis/messages/adapted_types/opening_count_array.hpp>
#include <sanguis/messages/adapted_types/seed.hpp>
#include <sanguis/messages/adapted_types/string.hpp>
#include <sanguis/messages/adapted_types/world_id.hpp>
#include <sanguis/messages/server/declare_message.hpp>
#include <sanguis/messages/server/change_world_fwd.hpp>
#include <alda/bindings/record_variadic.hpp>
#include <alda/message/object.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/record/element.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wweak-template-vtables)

SANGUIS_MESSAGES_SERVER_DECLARE_MESSAGE(
	sanguis::messages::server::change_world
);

FCPPT_PP_POP_WARNING

#endif
