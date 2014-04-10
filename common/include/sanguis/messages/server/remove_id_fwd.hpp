#ifndef SANGUIS_MESSAGES_SERVER_REMOVE_ID_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_REMOVE_ID_FWD_HPP_INCLUDED

#include <sanguis/messages/server/types/make_message_id_fwd.hpp>
#include <sanguis/messages/server/types/message.hpp>
#include <alda/message/make_class_fwd.hpp>


namespace sanguis
{
namespace messages
{
namespace server
{

typedef
alda::message::make_class<
	sanguis::messages::server::types::make_message_id<
		sanguis::messages::server::types::message::remove_id
	>
>
remove_id;

}
}
}

#endif
