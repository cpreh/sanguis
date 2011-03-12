#ifndef SANGUIS_MESSAGES_REMOVE_HPP_INCLUDED
#define SANGUIS_MESSAGES_REMOVE_HPP_INCLUDED

#include "bind_entity_message.hpp"
#include "make_class.hpp"
#include "types/message.hpp"

namespace sanguis
{
namespace messages
{

typedef make_class<
	bind_entity_message<
		types::message::remove
	>::type
>::type remove;

}
}

#endif
