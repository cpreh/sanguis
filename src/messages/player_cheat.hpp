#ifndef SANGUIS_MESSAGES_PLAYER_CHEAT_HPP_INCLUDED
#define SANGUIS_MESSAGES_PLAYER_CHEAT_HPP_INCLUDED

#include "bind_player_message.hpp"
#include "make_class.hpp"
#include "enum.hpp"
#include "types/message.hpp"
#include "roles/cheat.hpp"
#include <majutsu/composite.hpp>
#include <majutsu/role.hpp>
#include <boost/mpl/vector/vector10.hpp>

namespace sanguis
{
namespace messages
{

typedef messages::make_class<
	majutsu::composite<
		boost::mpl::vector2<
			messages::bind_player_message<
				types::message::player_cheat
			>::type,
			majutsu::role<
				messages::enum_,
				roles::cheat
			>
		>
	>
>::type player_cheat;

}
}

#endif
