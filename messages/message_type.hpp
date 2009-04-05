#ifndef SANGUIS_MESSAGES_MESSAGE_TYPE_HPP_INCLUDED
#define SANGUIS_MESSAGES_MESSAGE_TYPE_HPP_INCLUDED

#include "types/message_type.hpp"
#include <majutsu/pod.hpp>

namespace sanguis
{
namespace messages
{

typedef majutsu::pod<
	types::message_type
> message_type;

}
}

#endif
