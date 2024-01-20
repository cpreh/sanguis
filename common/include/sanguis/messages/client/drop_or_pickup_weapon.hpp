#ifndef SANGUIS_MESSAGES_CLIENT_DROP_OR_PICKUP_WEAPON_HPP_INCLUDED
#define SANGUIS_MESSAGES_CLIENT_DROP_OR_PICKUP_WEAPON_HPP_INCLUDED

#include <sanguis/messages/adapted_types/is_primary_weapon.hpp> // IWYU pragma: keep
#include <sanguis/messages/client/declare_message.hpp>
#include <sanguis/messages/client/drop_or_pickup_weapon_fwd.hpp> // IWYU pragma: export
#include <alda/message/object.hpp> // IWYU pragma: keep
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wweak-template-vtables)

SANGUIS_MESSAGES_CLIENT_DECLARE_MESSAGE(sanguis::messages::client::drop_or_pickup_weapon);

FCPPT_PP_POP_WARNING

#endif
