#ifndef SANGUIS_MESSAGES_ADD_PLAYER_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADD_PLAYER_HPP_INCLUDED

#include "roles/enemy.hpp"
#include "types/message.hpp"
#include "make_class.hpp"
#include "bind_entity_message.hpp"
#include "add_with_health.hpp"
#include "enum.hpp"
#include <majutsu/composite.hpp>
#include <majutsu/role.hpp>
#include <boost/mpl/vector.hpp>

namespace sanguis
{
namespace messages
{

typedef make_class<
	majutsu::composite<
		boost::mpl::vector<
			bind_entity_message<
				types::message::add_player
			>::type,
			add_with_health
		>
	>
>::type add_player;

}
}

#endif
