#ifndef SANGUIS_MESSAGES_STOP_RELOADING_HPP_INCLUDED
#define SANGUIS_MESSAGES_STOP_RELOADING_HPP_INCLUDED

#include "bind_entity_message.hpp"
#include "make_class.hpp"
#include "types/message.hpp"

namespace sanguis
{
namespace messages
{

typedef bind_entity_message<
	types::message::stop_reloading
>::type stop_reloading_elements;

typedef make_class<
	stop_reloading_elements
>::type stop_reloading;

}
}

#endif
