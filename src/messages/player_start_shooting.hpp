#ifndef SANGUIS_MESSAGES_PLAYER_START_SHOOTING_HPP_INCLUDED
#define SANGUIS_MESSAGES_PLAYER_START_SHOOTING_HPP_INCLUDED

#include "bind_player_message.hpp"
#include "make_class.hpp"
#include "types/message.hpp"

namespace sanguis
{
namespace messages
{

typedef messages::make_class<
	messages::bind_player_message<
		types::message::player_start_shooting
	>::type
>::type player_start_shooting;

}
}

#endif
