#ifndef SANGUIS_MESSAGES_SERVER_TYPES_BIND_ENTITY_MESSAGE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_TYPES_BIND_ENTITY_MESSAGE_FWD_HPP_INCLUDED

#include <sanguis/messages/server/parts/entity_message_fwd.hpp>
#include <sanguis/messages/server/types/make_message_id_fwd.hpp>
#include <sanguis/messages/server/types/message_fwd.hpp>
#include <majutsu/bind_fwd.hpp>
#include <majutsu/placeholder_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace messages
{
namespace server
{
namespace types
{

template<
	sanguis::messages::server::types::message Msg
>
using bind_entity_message
=
majutsu::bind<
	sanguis::messages::server::parts::entity_message,
	boost::mpl::vector2<
		sanguis::messages::server::types::make_message_id<
			Msg
		>,
		majutsu::placeholder
	>
>;

}
}
}
}

#endif
