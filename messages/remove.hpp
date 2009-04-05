#ifndef SANGUIS_MESSAGES_REMOVE_HPP_INCLUDED
#define SANGUIS_MESSAGES_REMOVE_HPP_INCLUDED

#include "bind_entity_message.hpp"
#include "make_class.hpp"
#include "types/message.hpp"

namespace sanguis
{
namespace messages
{

typedef bind_entity_message<
	types::message::remove
>::type remove_elements;

typedef make_class<
	remove_elements
>::type remove;

}
}

#endif
