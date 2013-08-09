#ifndef SANGUIS_MESSAGES_ADD_PICKUP_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADD_PICKUP_FWD_HPP_INCLUDED

#include <sanguis/pickup_type_fwd.hpp>
#include <sanguis/messages/add_elements_base_fwd.hpp>
#include <sanguis/messages/bind_entity_message_fwd.hpp>
#include <sanguis/messages/make_class_fwd.hpp>
#include <sanguis/messages/adapted_types/enum_fwd.hpp>
#include <sanguis/messages/roles/pickup.hpp>
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
		boost::mpl::vector3<
			sanguis::messages::bind_entity_message<
				sanguis::messages::types::message::add_pickup
			>,
			sanguis::messages::add_elements_base,
			majutsu::role<
				sanguis::messages::adapted_types::enum_<
					sanguis::pickup_type
				>,
				sanguis::messages::roles::pickup
			>
		>
	>
>
add_pickup;

}
}

#endif
