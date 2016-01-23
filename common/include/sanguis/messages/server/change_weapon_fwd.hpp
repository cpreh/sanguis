#ifndef SANGUIS_MESSAGES_SERVER_CHANGE_WEAPON_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_CHANGE_WEAPON_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/optional_primary_weapon_type_fwd.hpp>
#include <sanguis/messages/roles/primary_weapon.hpp>
#include <sanguis/messages/server/parts/entity_id_fwd.hpp>
#include <sanguis/messages/server/types/make_message_id_fwd.hpp>
#include <sanguis/messages/server/types/message.hpp>
#include <alda/message/record_fwd.hpp>
#include <majutsu/role_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace messages
{
namespace server
{

typedef
alda::message::record<
	sanguis::messages::server::types::make_message_id<
		sanguis::messages::server::types::message::change_weapon
	>,
	boost::mpl::vector2<
		sanguis::messages::server::parts::entity_id,
		majutsu::role<
			sanguis::messages::adapted_types::optional_primary_weapon_type,
			sanguis::messages::roles::primary_weapon
		>
	>
>
change_weapon;

}
}
}

#endif
