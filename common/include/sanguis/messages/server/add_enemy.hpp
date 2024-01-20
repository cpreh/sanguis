#ifndef SANGUIS_MESSAGES_SERVER_ADD_ENEMY_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_ADD_ENEMY_HPP_INCLUDED

#include <sanguis/enemy_kind.hpp> // IWYU pragma: keep
#include <sanguis/creator/enemy_type.hpp> // IWYU pragma: keep
#include <sanguis/messages/adapted_types/enum.hpp> // IWYU pragma: keep
#include <sanguis/messages/adapted_types/string.hpp> // IWYU pragma: keep
#include <sanguis/messages/server/add_enemy_fwd.hpp> // IWYU pragma: export
#include <sanguis/messages/server/declare_message.hpp>
#include <sanguis/messages/server/parts/add_actor.hpp> // IWYU pragma: keep
#include <sanguis/messages/server/parts/entity_id.hpp> // IWYU pragma: keep
#include <alda/bindings/record.hpp> // IWYU pragma: keep
#include <alda/message/object.hpp> // IWYU pragma: keep
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/record/element.hpp> // IWYU pragma: keep

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wweak-template-vtables)

SANGUIS_MESSAGES_SERVER_DECLARE_MESSAGE(sanguis::messages::server::add_enemy);

FCPPT_PP_POP_WARNING

#endif
