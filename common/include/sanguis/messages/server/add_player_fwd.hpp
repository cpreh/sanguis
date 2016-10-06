#ifndef SANGUIS_MESSAGES_SERVER_ADD_PLAYER_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_ADD_PLAYER_FWD_HPP_INCLUDED

#include <sanguis/messages/server/parts/add_player_fwd.hpp>
#include <sanguis/messages/server/parts/entity_id_fwd.hpp>
#include <sanguis/messages/server/types/make_message_id.hpp>
#include <sanguis/messages/server/types/message.hpp>
#include <alda/bindings/record_fwd.hpp>
#include <alda/message/object_fwd.hpp>
#include <fcppt/mpl/flatten.hpp>
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
alda::message::object<
	sanguis::messages::server::types::make_message_id<
		sanguis::messages::server::types::message::add_player
	>,
	alda::bindings::record<
		fcppt::mpl::flatten<
			boost::mpl::vector2<
				sanguis::messages::server::parts::entity_id,
				sanguis::messages::server::parts::add_player
			>
		>
	>
>
add_player;

}
}
}

#endif
