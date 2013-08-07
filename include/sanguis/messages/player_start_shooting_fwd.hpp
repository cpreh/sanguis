#ifndef SANGUIS_MESSAGES_PLAYER_START_SHOOTING_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_PLAYER_START_SHOOTING_FWD_HPP_INCLUDED

#include <sanguis/messages/bind_player_message_fwd.hpp>
#include <sanguis/messages/make_class_fwd.hpp>
#include <sanguis/messages/types/message.hpp>


namespace sanguis
{
namespace messages
{

typedef
sanguis::messages::make_class<
	sanguis::messages::bind_player_message<
		sanguis::messages::types::message::player_start_shooting
	>
>
player_start_shooting;

}
}

#endif
