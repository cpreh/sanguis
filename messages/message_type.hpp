#ifndef SANGUIS_MESSAGES_MESSAGE_TYPE_HPP_INCLUDED
#define SANGUIS_MESSAGES_MESSAGE_TYPE_HPP_INCLUDED

#include "types/message_type.hpp"
#include "bindings/pod.hpp"

namespace sanguis
{
namespace messages
{

typedef bindings::pod<
	types::message_type
> message_type;

}
}

#endif
