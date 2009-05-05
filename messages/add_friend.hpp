#ifndef SANGUIS_MESSAGES_ADD_FRIEND_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADD_FRIEND_HPP_INCLUDED

#include "make_add_message.hpp"
#include "make_class.hpp"
#include "enum.hpp"
#include "types/message.hpp"
#include "roles/friend.hpp"
#include <majutsu/role.hpp>
#include <boost/mpl/vector.hpp>

namespace sanguis
{
namespace messages
{

typedef make_add_message<
	types::message::add_friend,
	boost::mpl::vector<
		majutsu::role<
			enum_,
			roles::friend_
		>
	>
>::type add_friend_elements;

typedef make_class<
	add_friend_elements
>::type add_friend;

}
}

#endif
