#ifndef SANGUIS_MESSAGES_ADD_AOE_PROJECTILE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADD_AOE_PROJECTILE_FWD_HPP_INCLUDED

#include <sanguis/aoe_projectile_type_fwd.hpp>
#include <sanguis/messages/add_with_speed_fwd.hpp>
#include <sanguis/messages/bind_entity_message_fwd.hpp>
#include <sanguis/messages/make_class_fwd.hpp>
#include <sanguis/messages/adapted_types/enum_fwd.hpp>
#include <sanguis/messages/adapted_types/space_unit_fwd.hpp>
#include <sanguis/messages/roles/aoe_projectile.hpp>
#include <sanguis/messages/roles/aoe.hpp>
#include <sanguis/messages/types/message.hpp>
#include <majutsu/role_fwd.hpp>
#include <majutsu/composite_fwd.hpp>
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
		boost::mpl::vector4<
			sanguis::messages::bind_entity_message<
				sanguis::messages::types::message::add_aoe_projectile
			>,
			sanguis::messages::add_with_speed,
			majutsu::role<
				sanguis::messages::adapted_types::space_unit,
				sanguis::messages::roles::aoe
			>,
			majutsu::role<
				sanguis::messages::adapted_types::enum_<
					sanguis::aoe_projectile_type
				>,
				sanguis::messages::roles::aoe_projectile
			>
		>
	>
>
add_aoe_projectile;

}
}

#endif
