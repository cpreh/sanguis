#ifndef SANGUIS_MESSAGES_ADD_OWN_PLAYER_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADD_OWN_PLAYER_FWD_HPP_INCLUDED

#include <sanguis/messages/make_class_fwd.hpp>
#include <sanguis/messages/make_player_message_fwd.hpp>
#include <sanguis/messages/types/message.hpp>


namespace sanguis
{
namespace messages
{

typedef
sanguis::messages::make_class<
	sanguis::messages::make_player_message<
		sanguis::messages::types::message::add_own_player
	>
>
add_own_player;

}
}

#endif
