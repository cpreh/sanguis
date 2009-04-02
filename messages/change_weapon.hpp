#ifndef SANGUIS_MESSAGES_CHANGE_WEAPON_HPP_INCLUDED
#define SANGUIS_MESSAGES_CHANGE_WEAPON_HPP_INCLUDED

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
			types::message::change_weapon
		>::type,
		majutsu::role<
			enum_,
			roles::weapon
		>
	>
> change_weapon_elements;

typedef make_class<
	change_weapon_elements
>::type change_weapon;

}
}

#endif
