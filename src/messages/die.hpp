#ifndef SANGUIS_MESSAGES_DIE_HPP_INCLUDED
#define SANGUIS_MESSAGES_DIE_HPP_INCLUDED

#include "bind_entity_message.hpp"
#include "make_class.hpp"
#include "types/message.hpp"

namespace sanguis
{
namespace messages
{

typedef messages::make_class<
	messages::bind_entity_message<
		types::message::die
	>::type
>::type die;

}
}

#endif
