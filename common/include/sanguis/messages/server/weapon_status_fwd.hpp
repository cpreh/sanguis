#ifndef SANGUIS_MESSAGES_SERVER_WEAPON_STATUS_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_WEAPON_STATUS_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/weapon_status_fwd.hpp>
#include <sanguis/messages/roles/weapon_status.hpp>
#include <sanguis/messages/server/parts/entity_id_fwd.hpp>
#include <sanguis/messages/server/types/make_message_id.hpp>
#include <sanguis/messages/server/types/message.hpp>
#include <alda/message/record_fwd.hpp>
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
alda::message::record<
	sanguis::messages::server::types::make_message_id<
		sanguis::messages::server::types::message::weapon_status
	>,
	boost::mpl::vector2<
		sanguis::messages::server::parts::entity_id,
		majutsu::role<
			sanguis::messages::adapted_types::weapon_status,
			sanguis::messages::roles::weapon_status
		>
	>
>
weapon_status;

}
}
}

#endif
