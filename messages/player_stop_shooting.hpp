#ifndef SANGUIS_MESSAGES_PLAYER_STOP_SHOOTING_HPP_INCLUDED
#define SANGUIS_MESSAGES_PLAYER_STOP_SHOOTING_HPP_INCLUDED

#include "bind_entity_message.hpp"
#include "make_class.hpp"
#include "types/message.hpp"

namespace sanguis
{
namespace messages
{

typedef bind_entity_message<
	types::message::player_stop_shooting
>::type player_stop_shooting_elements;

typedef make_class<
	player_stop_shooting_elements
>::type player_stop_shooting;

}
}

#endif
