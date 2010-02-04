#ifndef SANGUIS_MESSAGES_ASSIGN_ID_HPP_INCLUDED
#define SANGUIS_MESSAGES_ASSIGN_ID_HPP_INCLUDED

#include "types/message.hpp"
#include "make_class.hpp"
#include "bind_entity_message.hpp"

namespace sanguis
{
namespace messages
{

typedef make_class<
	bind_entity_message<
		types::message::assign_id
	>::type
>::type assign_id;

}
}

#endif
