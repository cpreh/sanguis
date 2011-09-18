#ifndef SANGUIS_MESSAGES_REMOVE_HPP_INCLUDED
#define SANGUIS_MESSAGES_REMOVE_HPP_INCLUDED

#include <sanguis/messages/bind_entity_message.hpp>
#include <sanguis/messages/make_class.hpp>
#include <sanguis/messages/types/message.hpp>

namespace sanguis
{
namespace messages
{

typedef messages::make_class<
	messages::bind_entity_message<
		types::message::remove
	>::type
>::type remove;

}
}

#endif
