#ifndef SANGUIS_MESSAGES_CLIENT_CHANGE_WORLD_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_CLIENT_CHANGE_WORLD_FWD_HPP_INCLUDED

#include <sanguis/messages/client/types/make_message_id.hpp>
#include <sanguis/messages/client/types/message.hpp>
#include <alda/message/record_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace messages
{
namespace client
{

typedef
alda::message::record<
	sanguis::messages::client::types::make_message_id<
		sanguis::messages::client::types::message::change_world
	>,
	boost::mpl::vector0<>
>
change_world;

}
}
}

#endif
