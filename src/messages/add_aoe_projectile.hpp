#ifndef SANGUIS_MESSAGES_ADD_AOE_PROJECTILE_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADD_AOE_PROJECTILE_HPP_INCLUDED

#include "roles/aoe_projectile.hpp"
#include "roles/aoe.hpp"
#include "types/message.hpp"
#include "add_with_speed.hpp"
#include "bind_entity_message.hpp"
#include "make_class.hpp"
#include "space_unit.hpp"
#include "enum.hpp"
#include <majutsu/role.hpp>
#include <majutsu/composite.hpp>
#include <boost/mpl/vector/vector10.hpp>

namespace sanguis
{
namespace messages
{

typedef make_class<
	majutsu::composite<
		boost::mpl::vector4<
			bind_entity_message<
				types::message::add_aoe_projectile
			>::type,
			add_with_speed,
			majutsu::role<
				space_unit,
				roles::aoe
			>,
			majutsu::role<
				enum_,
				roles::aoe_projectile
			>
		>
	>
>::type add_aoe_projectile;

}
}

#endif
