#ifndef SANGUIS_MESSAGES_CLIENT_DROP_OR_PICKUP_WEAPON_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_CLIENT_DROP_OR_PICKUP_WEAPON_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/is_primary_weapon_fwd.hpp>
#include <sanguis/messages/client/types/make_message_id.hpp>
#include <sanguis/messages/client/types/message.hpp>
#include <sanguis/messages/roles/is_primary_weapon.hpp>
#include <alda/message/record_fwd.hpp>
#include <majutsu/role_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace messages
{
namespace client
{

typedef
alda::message::record<
	sanguis::messages::client::types::make_message_id<
		sanguis::messages::client::types::message::drop_or_pickup_weapon
	>,
	boost::mpl::vector1<
		majutsu::role<
			sanguis::messages::adapted_types::is_primary_weapon,
			sanguis::messages::roles::is_primary_weapon
		>
	>
>
drop_or_pickup_weapon;

}
}
}

#endif
