#ifndef SANGUIS_MESSAGES_MESSAGE_TYPE_HPP_INCLUDED
#define SANGUIS_MESSAGES_MESSAGE_TYPE_HPP_INCLUDED

#include "types/message_type.hpp"
#include "bindings/fundamental.hpp"

namespace sanguis
{
namespace messages
{

typedef bindings::fundamental<
	types::message_type
> message_type;

}
}

#endif
