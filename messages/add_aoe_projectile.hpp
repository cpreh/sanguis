#ifndef SANGUIS_MESSAGES_ADD_AOE_PROJECTILE_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADD_AOE_PROJECTILE_HPP_INCLUDED

#include "make_add_message.hpp"
#include "make_class.hpp"
#include "enum.hpp"
#include "types/message.hpp"
#include "roles/aoe_projectile.hpp"
#include "roles/aoe.hpp"
#include <majutsu/role.hpp>
#include <boost/mpl/vector.hpp>

namespace sanguis
{
namespace messages
{

typedef make_add_message<
	types::message::add_aoe_projectile,
	boost::mpl::vector<
		majutsu::role<
			space_unit,
			roles::aoe
		>,
		majutsu::role<
			enum_,
			roles::aoe_projectile
		>
	>
>::type add_aoe_projectile_elements;

typedef make_class<
	add_aoe_projectile_elements
>::type add_aoe_projectile;

}
}

#endif
