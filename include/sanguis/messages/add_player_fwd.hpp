#ifndef SANGUIS_MESSAGES_ADD_PLAYER_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADD_PLAYER_FWD_HPP_INCLUDED

#include <sanguis/messages/add_player_basic_fwd.hpp>
#include <sanguis/messages/make_class_fwd.hpp>
#include <sanguis/messages/types/message.hpp>


namespace sanguis
{
namespace messages
{

typedef
sanguis::messages::make_class<
	sanguis::messages::add_player_basic<
		sanguis::messages::types::message::add_player
	>
>
add_player;

}
}

#endif
