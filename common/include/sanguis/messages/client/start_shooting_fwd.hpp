#ifndef SANGUIS_MESSAGES_CLIENT_START_SHOOTING_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_CLIENT_START_SHOOTING_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/is_primary_weapon_fwd.hpp>
#include <sanguis/messages/client/types/make_message_id.hpp>
#include <sanguis/messages/client/types/message.hpp>
#include <alda/message/object_fwd.hpp>


namespace sanguis::messages::client
{

using
start_shooting
=
alda::message::object<
	sanguis::messages::client::types::make_message_id<
		sanguis::messages::client::types::message::start_shooting
	>,
	sanguis::messages::adapted_types::is_primary_weapon
>;

}

#endif
