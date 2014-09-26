#ifndef SANGUIS_MESSAGES_SERVER_ADD_AOE_PROJECTILE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_ADD_AOE_PROJECTILE_FWD_HPP_INCLUDED

#include <sanguis/aoe_projectile_type_fwd.hpp>
#include <sanguis/messages/adapted_types/enum_fwd.hpp>
#include <sanguis/messages/adapted_types/space_unit_fwd.hpp>
#include <sanguis/messages/roles/aoe.hpp>
#include <sanguis/messages/roles/aoe_projectile_type.hpp>
#include <sanguis/messages/server/parts/add_elements_base_fwd.hpp>
#include <sanguis/messages/server/parts/speed_fwd.hpp>
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
		boost::mpl::vector5<
			sanguis::messages::server::types::bind_entity_message<
				sanguis::messages::server::types::message::add_aoe_projectile
			>,
			sanguis::messages::server::parts::add_elements_base,
			sanguis::messages::server::parts::speed,
			majutsu::role<
				sanguis::messages::adapted_types::space_unit,
				sanguis::messages::roles::aoe
			>,
			majutsu::role<
				sanguis::messages::adapted_types::enum_<
					sanguis::aoe_projectile_type
				>,
				sanguis::messages::roles::aoe_projectile_type
			>
		>
	>
>
add_aoe_projectile;

}
}
}

#endif
