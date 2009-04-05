#ifndef SANGUIS_MESSAGES_ADD_WEAPON_PICKUP_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADD_WEAPON_PICKUP_HPP_INCLUDED

#include "make_add_message.hpp"
#include "make_class.hpp"
#include "enum.hpp"
#include "types/message.hpp"
#include "roles/weapon.hpp"
#include <majutsu/role.hpp>
#include <boost/mpl/vector.hpp>

namespace sanguis
{
namespace messages
{

typedef make_add_message<
	types::message::add_weapon_pickup,
	boost::mpl::vector<
		majutsu::role<
			enum_,
			roles::weapon
		>
	>
>::type add_weapon_pickup_elements;

typedef make_class<
	add_weapon_pickup_elements
>::type add_weapon_pickup;

}
}

#endif
