#ifndef SANGUIS_MESSAGES_PLAYER_ATTACK_DEST_HPP_INCLUDED
#define SANGUIS_MESSAGES_PLAYER_ATTACK_DEST_HPP_INCLUDED

#include "bind_entity_message.hpp"
#include "make_class.hpp"
#include "pos.hpp"
#include "types/message.hpp"
#include "roles/attack_dest.hpp"
#include <majutsu/composite.hpp>
#include <majutsu/role.hpp>
#include <boost/mpl/vector/vector10.hpp>

namespace sanguis
{
namespace messages
{

typedef majutsu::composite<
	boost::mpl::vector2<
		bind_entity_message<
			types::message::player_attack_dest
		>::type,
		majutsu::role<
			pos,
			roles::attack_dest
		>
	>
> player_attack_dest_elements;

typedef make_class<
	player_attack_dest_elements
>::type player_attack_dest;

}
}

#endif
