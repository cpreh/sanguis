#ifndef SANGUIS_MESSAGES_STOP_ATTACKING_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_STOP_ATTACKING_FWD_HPP_INCLUDED

#include <sanguis/messages/bind_entity_message_fwd.hpp>
#include <sanguis/messages/make_class_fwd.hpp>
#include <sanguis/messages/types/message.hpp>


namespace sanguis
{
namespace messages
{

typedef
sanguis::messages::make_class<
	sanguis::messages::bind_entity_message<
		sanguis::messages::types::message::stop_attacking
	>
>
stop_attacking;

}
}

#endif
