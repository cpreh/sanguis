#ifndef SANGUIS_MESSAGES_CLIENT_DROP_OR_PICKUP_WEAPON_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_CLIENT_DROP_OR_PICKUP_WEAPON_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/is_primary_weapon_fwd.hpp>
#include <sanguis/messages/client/types/make_message_id.hpp>
#include <sanguis/messages/client/types/message.hpp>
#include <alda/message/object_fwd.hpp>


namespace sanguis
{
namespace messages
{
namespace client
{

typedef
alda::message::object<
	sanguis::messages::client::types::make_message_id<
		sanguis::messages::client::types::message::drop_or_pickup_weapon
	>,
	sanguis::messages::adapted_types::is_primary_weapon
>
drop_or_pickup_weapon;

}
}
}

#endif
