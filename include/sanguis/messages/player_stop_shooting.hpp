#ifndef SANGUIS_MESSAGES_PLAYER_STOP_SHOOTING_HPP_INCLUDED
#define SANGUIS_MESSAGES_PLAYER_STOP_SHOOTING_HPP_INCLUDED

#include <sanguis/messages/bind_player_message.hpp>
#include <sanguis/messages/make_class.hpp>
#include <sanguis/messages/types/message.hpp>


namespace sanguis
{
namespace messages
{

typedef sanguis::messages::make_class<
	sanguis::messages::bind_player_message<
		sanguis::messages::types::message::player_stop_shooting
	>::type
>::type player_stop_shooting;

}
}

#endif
