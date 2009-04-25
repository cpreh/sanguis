#ifndef SANGUIS_MESSAGES_PLAYER_ROTATION_HPP_INCLUDED
#define SANGUIS_MESSAGES_PLAYER_ROTATION_HPP_INCLUDED

#include "bind_entity_message.hpp"
#include "make_class.hpp"
#include "space_unit.hpp"
#include "types/message.hpp"
#include "roles/angle.hpp"
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
			types::message::player_rotation
		>::type,
		majutsu::role<
			space_unit,
			roles::angle
		>
	>
> player_rotation_types;

typedef make_class<
	player_rotation_types
>::type player_rotation;

}
}

#endif
