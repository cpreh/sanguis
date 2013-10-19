#ifndef SANGUIS_MESSAGES_ADD_FRIEND_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADD_FRIEND_FWD_HPP_INCLUDED

#include <sanguis/friend_type_fwd.hpp>
#include <sanguis/messages/add_with_buffs_fwd.hpp>
#include <sanguis/messages/bind_entity_message_fwd.hpp>
#include <sanguis/messages/make_class_fwd.hpp>
#include <sanguis/messages/adapted_types/enum_fwd.hpp>
#include <sanguis/messages/roles/friend.hpp>
#include <sanguis/messages/types/message.hpp>
#include <majutsu/composite_fwd.hpp>
#include <majutsu/role_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace messages
{

typedef
sanguis::messages::make_class<
	majutsu::composite<
		boost::mpl::vector3<
			sanguis::messages::bind_entity_message<
				sanguis::messages::types::message::add_friend
			>,
			sanguis::messages::add_with_buffs,
			majutsu::role<
				sanguis::messages::adapted_types::enum_<
					sanguis::friend_type
				>,
				sanguis::messages::roles::friend_
			>
		>
	>
>
add_friend;

}
}

#endif
