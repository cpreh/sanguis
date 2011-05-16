#ifndef SANGUIS_MESSAGES_REMOVE_ID_HPP_INCLUDED
#define SANGUIS_MESSAGES_REMOVE_ID_HPP_INCLUDED

#include "types/message.hpp"
#include "make_message_id.hpp"
#include "make_class.hpp"

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
