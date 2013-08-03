#ifndef SANGUIS_MESSAGES_START_ATTACKING_HPP_INCLUDED
#define SANGUIS_MESSAGES_START_ATTACKING_HPP_INCLUDED

#include <sanguis/messages/bind_entity_message.hpp>
#include <sanguis/messages/make_class.hpp>
#include <sanguis/messages/types/message.hpp>


namespace sanguis
{
namespace messages
{

typedef
sanguis::messages::make_class<
	sanguis::messages::bind_entity_message<
		sanguis::messages::types::message::start_attacking
	>
>
start_attacking;

}
}

#endif
