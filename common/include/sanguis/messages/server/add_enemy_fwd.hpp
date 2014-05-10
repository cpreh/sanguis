#ifndef SANGUIS_MESSAGES_SERVER_ADD_ENEMY_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_ADD_ENEMY_FWD_HPP_INCLUDED

#include <sanguis/creator/enemy_type_fwd.hpp>
#include <sanguis/messages/adapted_types/enum_fwd.hpp>
#include <sanguis/messages/adapted_types/string_fwd.hpp>
#include <sanguis/messages/roles/enemy_type.hpp>
#include <sanguis/messages/roles/name.hpp>
#include <sanguis/messages/server/parts/add_actor_fwd.hpp>
#include <sanguis/messages/server/types/bind_entity_message_fwd.hpp>
#include <sanguis/messages/server/types/message.hpp>
#include <alda/message/make_class_fwd.hpp>
#include <majutsu/composite_fwd.hpp>
#include <majutsu/role_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace messages
{
namespace server
{

typedef
alda::message::make_class<
	majutsu::composite<
		boost::mpl::vector4<
			sanguis::messages::server::types::bind_entity_message<
				sanguis::messages::server::types::message::add_enemy
			>,
			sanguis::messages::server::parts::add_actor,
			majutsu::role<
				sanguis::messages::adapted_types::enum_<
					sanguis::creator::enemy_type
				>,
				sanguis::messages::roles::enemy_type
			>,
			majutsu::role<
				sanguis::messages::adapted_types::string,
				sanguis::messages::roles::name
			>
		>
	>
>
add_enemy;

}
}
}

#endif
