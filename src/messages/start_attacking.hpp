#ifndef SANGUIS_MESSAGES_START_ATTACKING_HPP_INCLUDED
#define SANGUIS_MESSAGES_START_ATTACKING_HPP_INCLUDED

#include "bind_entity_message.hpp"
#include "make_class.hpp"
#include "types/message.hpp"

namespace sanguis
{
namespace messages
{

typedef bind_entity_message<
	types::message::start_attacking
>::type start_attacking_elements;

typedef make_class<
	start_attacking_elements
>::type start_attacking;

}
}

#endif
