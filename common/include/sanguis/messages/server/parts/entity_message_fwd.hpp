#ifndef SANGUIS_MESSAGES_SERVER_PARTS_ENTITY_MESSAGE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_PARTS_ENTITY_MESSAGE_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/entity_id.hpp>
#include <sanguis/messages/roles/entity_id.hpp>
#include <sanguis/messages/server/types/make_message_id_fwd.hpp>
#include <sanguis/messages/server/types/message_fwd.hpp>
#include <majutsu/role.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace messages
{
namespace server
{
namespace parts
{

template<
	sanguis::messages::server::types::message Msg
>
using
entity_message
=
boost::mpl::vector2<
	sanguis::messages::server::types::make_message_id<
		Msg
	>,
	majutsu::role<
		sanguis::messages::adapted_types::entity_id,
		sanguis::messages::roles::entity_id
	>
>;

}
}
}
}

#endif
