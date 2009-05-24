#ifndef SANGUIS_MESSAGES_PLAYER_CHEAT_HPP_INCLUDED
#define SANGUIS_MESSAGES_PLAYER_CHEAT_HPP_INCLUDED

#include "bind_entity_message.hpp"
#include "make_class.hpp"
#include "enum.hpp"
#include "types/message.hpp"
#include "roles/cheat.hpp"
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
			types::message::player_cheat
		>::type,
		majutsu::role<
			enum_,
			roles::cheat
		>
	>
> player_cheat_elements;

typedef make_class<
	player_cheat_elements
>::type player_cheat;

}
}


#endif
