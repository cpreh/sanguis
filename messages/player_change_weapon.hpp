#ifndef SANGUIS_MESSAGES_PLAYER_CHANGE_WEAPON_HPP_INCLUDED
#define SANGUIS_MESSAGES_PLAYER_CHANGE_WEAPON_HPP_INCLUDED

#include "roles/weapon.hpp"
#include "types/message.hpp"
#include "bind_entity_message.hpp"
#include "enum.hpp"
#include "make_class.hpp"
#include <majutsu/composite.hpp>
#include <majutsu/role.hpp>
#include <boost/mpl/vector.hpp>

namespace sanguis
{
namespace messages
{

typedef majutsu::composite<
	boost::mpl::vector<
		bind_entity_message<
			types::message::player_change_weapon
		>,
		majutsu::role<
			enum_,
			roles::weapon
		>
	>
> player_change_weapon_elements;

typedef make_class<
	player_change_weapon_elements
>::type player_change_weapon;

}
}

#endif
