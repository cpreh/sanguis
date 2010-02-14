#ifndef SANGUIS_MESSAGES_ADD_OWN_PLAYER_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADD_OWN_PLAYER_HPP_INCLUDED

#include "types/message.hpp"
#include "make_class.hpp"
#include "make_player_message.hpp"

namespace sanguis
{
namespace messages
{

typedef make_class<
	make_player_message<
		types::message::add_own_player
	>::type
>::type add_own_player;

}
}

#endif
