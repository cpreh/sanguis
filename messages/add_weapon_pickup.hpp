#ifndef SANGUIS_MESSAGES_ADD_WEAPON_PICKUP_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADD_WEAPON_PICKUP_HPP_INCLUDED

#include "roles/weapon.hpp"
#include "types/message.hpp"
#include "bind_entity_message.hpp"
#include "make_class.hpp"
#include "enum.hpp"
#include "add_elements_base.hpp"
#include <majutsu/role.hpp>
#include <majutsu/composite.hpp>
#include <boost/mpl/vector.hpp>

namespace sanguis
{
namespace messages
{

typedef make_class<
	majutsu::composite<
		boost::mpl::vector<
			bind_entity_message<
				types::message::add_weapon_pickup
			>::type,
			add_elements_base,
			majutsu::role<
				enum_,
				roles::weapon
			>
		>
	>
>::type add_weapon_pickup;

}
}

#endif
