#ifndef SANGUIS_MESSAGES_SERVER_CHANGE_WEAPON_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_CHANGE_WEAPON_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/optional_primary_weapon_type_fwd.hpp>
#include <sanguis/messages/roles/primary_weapon.hpp>
#include <sanguis/messages/server/parts/entity_id_fwd.hpp>
#include <sanguis/messages/server/types/make_message_id.hpp>
#include <sanguis/messages/server/types/message.hpp>
#include <alda/bindings/record_variadic_fwd.hpp>
#include <alda/message/object_fwd.hpp>
#include <fcppt/record/element_fwd.hpp>


namespace sanguis
{
namespace messages
{
namespace server
{

using
change_weapon
=
alda::message::object<
	sanguis::messages::server::types::make_message_id<
		sanguis::messages::server::types::message::change_weapon
	>,
	alda::bindings::record_variadic<
		sanguis::messages::server::parts::entity_id,
		fcppt::record::element<
			sanguis::messages::roles::primary_weapon,
			sanguis::messages::adapted_types::optional_primary_weapon_type
		>
	>
>;

}
}
}

#endif
