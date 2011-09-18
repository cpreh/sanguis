#ifndef SANGUIS_MESSAGES_REMOVE_ID_HPP_INCLUDED
#define SANGUIS_MESSAGES_REMOVE_ID_HPP_INCLUDED

#include <sanguis/messages/types/message.hpp>
#include <sanguis/messages/make_message_id.hpp>
#include <sanguis/messages/make_class.hpp>

namespace sanguis
{
namespace messages
{

typedef messages::make_class<
	messages::make_message_id<
		types::message::remove_id
	>::type
>::type remove_id;

}
}

#endif
