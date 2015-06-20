#ifndef SANGUIS_MESSAGES_SERVER_HEALTH_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_HEALTH_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/space_unit_fwd.hpp>
#include <sanguis/messages/roles/health.hpp>
#include <sanguis/messages/server/parts/entity_message_fwd.hpp>
#include <sanguis/messages/server/types/message.hpp>
#include <alda/message/make_class_fwd.hpp>
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
	boost::mpl::vector2<
		sanguis::messages::server::parts::entity_message<
			sanguis::messages::server::types::message::health
		>,
		majutsu::role<
			sanguis::messages::adapted_types::space_unit,
			sanguis::messages::roles::health
		>
	>
>
health;

}
}
}

#endif
