#ifndef SANGUIS_MESSAGES_STOP_ATTACKING_HPP_INCLUDED
#define SANGUIS_MESSAGES_STOP_ATTACKING_HPP_INCLUDED

#include "bind_entity_message.hpp"
#include "make_class.hpp"
#include "types/message.hpp"

namespace sanguis
{
namespace messages
{

typedef bind_entity_message<
	types::message::stop_attacking
>::type stop_attacking_elements;

typedef make_class<
	stop_attacking_elements
>::type stop_attacking;

}
}

#endif
