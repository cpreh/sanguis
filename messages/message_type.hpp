#ifndef SANGUIS_MESSAGES_MESSAGE_TYPE_HPP_INCLUDED
#define SANGUIS_MESSAGES_MESSAGE_TYPE_HPP_INCLUDED

#include "types/enum.hpp"
#include <majutsu/pod.hpp>

namespace sanguis
{
namespace messages
{

typedef majutsu::pod<
	types::enum_
> message_type;

}
}

#endif
