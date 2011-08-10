#ifndef SANGUIS_MESSAGES_PLAYER_ATTACK_DEST_HPP_INCLUDED
#define SANGUIS_MESSAGES_PLAYER_ATTACK_DEST_HPP_INCLUDED

#include "bind_player_message.hpp"
#include "make_class.hpp"
#include "vector2.hpp"
#include "types/message.hpp"
#include "roles/attack_dest.hpp"
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
				types::message::player_attack_dest
			>::type,
			majutsu::role<
				messages::vector2,
				roles::attack_dest
			>
		>
	>
>::type player_attack_dest;

}
}

#endif
