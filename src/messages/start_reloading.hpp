#ifndef SANGUIS_MESSAGES_START_RELOADING_HPP_INCLUDED
#define SANGUIS_MESSAGES_START_RELOADING_HPP_INCLUDED

#include "bind_entity_message.hpp"
#include "make_class.hpp"
#include "types/message.hpp"

namespace sanguis
{
namespace messages
{

typedef bind_entity_message<
	types::message::start_reloading
>::type start_reloading_elements;

typedef make_class<
	start_reloading_elements
>::type start_reloading;

}
}

#endif
