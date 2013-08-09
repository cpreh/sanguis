#ifndef SANGUIS_MESSAGES_MAX_HEALTH_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_MAX_HEALTH_FWD_HPP_INCLUDED

#include <sanguis/messages/bind_entity_message_fwd.hpp>
#include <sanguis/messages/make_class_fwd.hpp>
#include <sanguis/messages/adapted_types/space_unit_fwd.hpp>
#include <sanguis/messages/roles/max_health.hpp>
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
		boost::mpl::vector2<
			sanguis::messages::bind_entity_message<
				sanguis::messages::types::message::max_health
			>,
			majutsu::role<
				sanguis::messages::adapted_types::space_unit,
				sanguis::messages::roles::max_health
			>
		>
	>
>
max_health;

}
}

#endif
