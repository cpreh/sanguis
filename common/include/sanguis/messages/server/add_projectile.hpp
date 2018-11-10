#ifndef SANGUIS_MESSAGES_SERVER_ADD_PROJECTILE_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_ADD_PROJECTILE_HPP_INCLUDED

#include <sanguis/projectile_type.hpp>
#include <sanguis/messages/adapted_types/enum.hpp>
#include <sanguis/messages/server/add_projectile_fwd.hpp>
#include <sanguis/messages/server/declare_message.hpp>
#include <sanguis/messages/server/parts/add_elements_base.hpp>
#include <sanguis/messages/server/parts/entity_id.hpp>
#include <sanguis/messages/server/parts/speed.hpp>
#include <alda/bindings/record.hpp>
#include <alda/message/object.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/record/element.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wweak-template-vtables)

SANGUIS_MESSAGES_SERVER_DECLARE_MESSAGE(
	sanguis::messages::server::add_projectile
);

FCPPT_PP_POP_WARNING

#endif
