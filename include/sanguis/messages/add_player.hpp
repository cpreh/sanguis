#ifndef SANGUIS_MESSAGES_ADD_PLAYER_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADD_PLAYER_HPP_INCLUDED

#include <sanguis/messages/make_class.hpp>
#include <sanguis/messages/make_player_message.hpp>
#include <sanguis/messages/types/message.hpp>


namespace sanguis
{
namespace messages
{

typedef
sanguis::messages::make_class<
	sanguis::messages::make_player_message<
		sanguis::messages::types::message::add_player
	>
>
add_player;

}
}

#endif
