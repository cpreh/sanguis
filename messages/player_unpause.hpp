#ifndef SANGUIS_MESSAGES_PLAYER_UNPAUSE_HPP_INCLUDED
#define SANGUIS_MESSAGES_PLAYER_UNPAUSE_HPP_INCLUDED

#include "bind_player_message.hpp"
#include "make_class.hpp"
#include "types/message.hpp"

namespace sanguis
{
namespace messages
{

typedef bind_player_message<
	types::message::player_unpause
>::type player_unpause_elements;

typedef make_class<
	player_unpause_elements
>::type player_unpause;

}
}

#endif
