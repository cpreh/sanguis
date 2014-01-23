#ifndef SANGUIS_MESSAGES_SERVER_ADD_PLAYER_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_ADD_PLAYER_FWD_HPP_INCLUDED

#include <sanguis/messages/server/parts/add_actor_fwd.hpp>
#include <sanguis/messages/server/types/bind_entity_message_fwd.hpp>
#include <sanguis/messages/server/types/message.hpp>
#include <alda/message/make_class_fwd.hpp>
#include <majutsu/composite_fwd.hpp>
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
		boost::mpl::vector2<
			sanguis::messages::server::types::bind_entity_message<
				sanguis::messages::server::types::message::add_player
			>,
			sanguis::messages::server::parts::add_actor
		>
	>
>
add_player;

}
}
}

#endif
