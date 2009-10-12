#ifndef SANGUIS_MESSAGES_ADD_FRIEND_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADD_FRIEND_HPP_INCLUDED

#include "roles/friend.hpp"
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
				types::message::add_friend
			>::type,
			add_with_health,
			majutsu::role<
				enum_,
				roles::friend_
			>
		>
	>
>::type add_friend;

}
}

#endif
