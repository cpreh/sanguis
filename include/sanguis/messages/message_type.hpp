#ifndef SANGUIS_MESSAGES_MESSAGE_TYPE_HPP_INCLUDED
#define SANGUIS_MESSAGES_MESSAGE_TYPE_HPP_INCLUDED

#include <sanguis/messages/types/message_type.hpp>
#include <sanguis/messages/bindings/fundamental.hpp>

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
