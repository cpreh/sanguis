#ifndef SANGUIS_MESSAGES_ADD_PROJECTILE_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADD_PROJECTILE_HPP_INCLUDED

#include "roles/projectile.hpp"
#include "types/message.hpp"
#include "add_with_speed.hpp"
#include "bind_entity_message.hpp"
#include "make_class.hpp"
#include "enum.hpp"
#include <majutsu/role.hpp>
#include <majutsu/composite.hpp>
#include <boost/mpl/vector/vector10.hpp>

namespace sanguis
{
namespace messages
{

typedef messages::make_class<
	majutsu::composite<
		boost::mpl::vector3<
			messages::bind_entity_message<
				types::message::add_projectile
			>::type,
			messages::add_with_speed,
			majutsu::role<
				messages::enum_,
				roles::projectile
			>
		>
	>
>::type add_projectile;

}
}

#endif
