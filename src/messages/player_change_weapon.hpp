#ifndef SANGUIS_MESSAGES_PLAYER_CHANGE_WEAPON_HPP_INCLUDED
#define SANGUIS_MESSAGES_PLAYER_CHANGE_WEAPON_HPP_INCLUDED

#include "roles/weapon.hpp"
#include "types/message.hpp"
#include "bind_player_message.hpp"
#include "enum.hpp"
#include "make_class.hpp"
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
				types::message::player_change_weapon
			>::type,
			majutsu::role<
				messages::enum_,
				roles::weapon
			>
		>
	>
>::type player_change_weapon;

}
}

#endif
