#ifndef SANGUIS_MESSAGES_SERVER_REMOVE_WEAPON_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_REMOVE_WEAPON_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/is_primary_weapon_fwd.hpp>
#include <sanguis/messages/server/types/make_message_id.hpp>
#include <sanguis/messages/server/types/message.hpp>
#include <alda/message/object_fwd.hpp>

namespace sanguis::messages::server
{

using remove_weapon = alda::message::object<
    sanguis::messages::server::types::make_message_id<
        sanguis::messages::server::types::message::remove_weapon>,
    sanguis::messages::adapted_types::is_primary_weapon>;

}

#endif
