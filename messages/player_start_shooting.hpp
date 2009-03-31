#ifndef SANGUIS_MESSAGES_PLAYER_START_SHOOTING_HPP_INCLUDED
#define SANGUIS_MESSAGES_PLAYER_START_SHOOTING_HPP_INCLUDED

#include "bind_entity_message.hpp"
#include "make_class.hpp"
#include "types/message.hpp"

namespace sanguis
{
namespace messages
{

typedef bind_entity_message<
	types::message::player_start_shooting
>::type player_start_shooting_elements;

typedef make_class<
	player_start_shooting_elements
> player_start_shooting;

}
}

#endif
