#ifndef SANGUIS_MESSAGES_SERVER_GIVE_WEAPON_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_GIVE_WEAPON_FWD_HPP_INCLUDED

#include <sanguis/messages/server/parts/weapon_description_fwd.hpp>
#include <sanguis/messages/server/types/make_message_id.hpp>
#include <sanguis/messages/server/types/message.hpp>
#include <alda/bindings/record_fwd.hpp>
#include <alda/message/object_fwd.hpp>


namespace sanguis::messages::server
{

using
give_weapon
=
alda::message::object<
	sanguis::messages::server::types::make_message_id<
		sanguis::messages::server::types::message::give_weapon
	>,
	alda::bindings::record<
		sanguis::messages::server::parts::weapon_description
	>
>;

}

#endif
