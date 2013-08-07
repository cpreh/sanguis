#ifndef SANGUIS_MESSAGES_ADD_ENEMY_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADD_ENEMY_FWD_HPP_INCLUDED

#include <sanguis/creator/enemy_type_fwd.hpp>
#include <sanguis/messages/add_with_health_fwd.hpp>
#include <sanguis/messages/bind_entity_message_fwd.hpp>
#include <sanguis/messages/enum_fwd.hpp>
#include <sanguis/messages/make_class_fwd.hpp>
#include <sanguis/messages/roles/enemy.hpp>
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
				sanguis::messages::types::message::add_enemy
			>,
			sanguis::messages::add_with_health,
			majutsu::role<
				sanguis::messages::enum_<
					sanguis::creator::enemy_type
				>,
				sanguis::messages::roles::enemy
			>
		>
	>
>
add_enemy;

}
}

#endif
