#ifndef SANGUIS_MESSAGES_PLAYER_DIRECTION_HPP_INCLUDED
#define SANGUIS_MESSAGES_PLAYER_DIRECTION_HPP_INCLUDED

#include "bind_player_message.hpp"
#include "make_class.hpp"
#include "vector2.hpp"
#include "types/message.hpp"
#include "roles/direction.hpp"
#include <majutsu/composite.hpp>
#include <majutsu/role.hpp>
#include <boost/mpl/vector/vector10.hpp>

namespace sanguis
{
namespace messages
{

typedef majutsu::composite<
	boost::mpl::vector2<
		bind_player_message<
			types::message::player_direction
		>::type,
		majutsu::role<
			vector2,
			roles::direction
		>
	>
> player_direction_elements;

typedef make_class<
	player_direction_elements
>::type player_direction;

}
}

#endif
