#ifndef SANGUIS_MESSAGES_SERVER_GIVE_WEAPON_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_GIVE_WEAPON_FWD_HPP_INCLUDED

#include <sanguis/messages/server/parts/weapon_description_fwd.hpp>
#include <sanguis/messages/server/types/make_message_id_fwd.hpp>
#include <sanguis/messages/server/types/message.hpp>
#include <alda/message/record_fwd.hpp>


namespace sanguis
{
namespace messages
{
namespace server
{

typedef
alda::message::record<
	sanguis::messages::server::types::make_message_id<
		sanguis::messages::server::types::message::give_weapon
	>,
	sanguis::messages::server::parts::weapon_description
>
give_weapon;

}
}
}

#endif
