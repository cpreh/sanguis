#ifndef SANGUIS_MESSAGES_PLAYER_PAUSE_HPP_INCLUDED
#define SANGUIS_MESSAGES_PLAYER_PAUSE_HPP_INCLUDED

#include "bind_entity_message.hpp"
#include "make_class.hpp"
#include "types/message.hpp"

namespace sanguis
{
namespace messages
{

typedef bind_entity_message<
	types::message::player_pause
>::type player_pause_elements;

typedef make_class<
	player_pause_elements
>::type player_pause;

}
}

#endif
