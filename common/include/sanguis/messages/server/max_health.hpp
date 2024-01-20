#ifndef SANGUIS_MESSAGES_SERVER_MAX_HEALTH_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_MAX_HEALTH_HPP_INCLUDED

#include <sanguis/messages/adapted_types/space_unit.hpp> // IWYU pragma: keep
#include <sanguis/messages/server/declare_message.hpp>
#include <sanguis/messages/server/max_health_fwd.hpp> // IWYU pragma: export
#include <sanguis/messages/server/parts/entity_id.hpp> // IWYU pragma: keep
#include <alda/bindings/record_variadic.hpp> // IWYU pragma: keep
#include <alda/message/object.hpp> // IWYU pragma: keep
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/record/element.hpp> // IWYU pragma: keep

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wweak-template-vtables)

SANGUIS_MESSAGES_SERVER_DECLARE_MESSAGE(sanguis::messages::server::max_health);

FCPPT_PP_POP_WARNING

#endif
