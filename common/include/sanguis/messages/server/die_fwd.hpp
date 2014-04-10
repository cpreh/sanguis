#ifndef SANGUIS_MESSAGES_SERVER_DIE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_DIE_FWD_HPP_INCLUDED

#include <sanguis/messages/server/types/bind_entity_message_fwd.hpp>
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
	sanguis::messages::server::types::bind_entity_message<
		sanguis::messages::server::types::message::die
	>
>
die;

}
}
}

#endif
