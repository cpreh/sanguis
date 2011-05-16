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
#include <boost/mpl/vector/vector10.hpp>

namespace sanguis
{
namespace messages
{

typedef messages::make_class<
	majutsu::composite<
		boost::mpl::vector3<
			messages::bind_entity_message<
				types::message::add_friend
			>::type,
			messages::add_with_health,
			majutsu::role<
				messages::enum_,
				roles::friend_
			>
		>
	>
>::type add_friend;

}
}

#endif
